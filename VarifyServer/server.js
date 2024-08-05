const grpc = require("@grpc/grpc-js");
const message_proto = require("./proto");
const const_module = require("./const");
const { v4: uuidv4 } = require("uuid");
const emailModule = require("./email");
const redisModule = require("./redis");
async function GetVarifyCode(call, callback) {
  console.log("Email: ", call.request.email);
  try {
    let query_res = await redisModule.GetRedis(
      const_module.code_prefix + call.request.email
    );
    console.log("query result is: ", query_res);
    let uniqueId = query_res;
    if (query_res == null) {
      uniqueId = uuidv4();
      if (uniqueId.length > 4) {
        uniqueId = uniqueId.substring(0, 4);
      }
    }
    let bres = await redisModule.SetRedisExpire(const_module.code_prefix+call.request.email, uniqueId, 180)
    if(!bres)
        {
            callback(null, { 
                email: call.request.email,
                error: const_module.Errors.RedisErr
            });
            return ;
        }
    console.log("UniqueId: ", uniqueId);
    let text_str = "Your varify code is: " + uniqueId + " will be expired in 3 minutes.";
    let mailOptions = {
      from: "magicsong.lunar@qq.com",
      to: call.request.email,
      subject: "Varify Code",
      text: text_str,
    };
    let send_res = await emailModule.SendMail(mailOptions);
    console.log("send res is ", send_res);
    if(!send_res)
      {
        callback(null, { 
            email: call.request.email,
            error: const_module.Errors.RedisErr
        });
      }
    callback(null, {
      email: call.request.email,
      error: const_module.Errors.Success,
    });
  } catch (error) {
    console.log("catch error is ", error);
    callback(null, {
      email: call.request.email,
      error: const_module.Errors.Exception,
    });
  }
}
function main() {
  var server = new grpc.Server();
  server.addService(message_proto.VarifyService.service, {
    GetVarifyCode: GetVarifyCode,
  });
  server.bindAsync(
    "0.0.0.0:50051",
    grpc.ServerCredentials.createInsecure(),
    () => {
      server.start();
      console.log("grpc server started!");
    }
  );
}
main();
