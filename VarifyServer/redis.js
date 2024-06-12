const config_module = require("./config");
const Redis = require("ioredis");

const Rediscli = new Redis({
  host: config_module.redis_host,
  port: config_module.redis_port,
  password: config_module.redis_passwd,
});
Rediscli.on("error", function (err) {
  console.log("redis error: " + err);
  Rediscli.quit();
});
/*
 * 根据key获取value
 * @param {*} key
 * @returns
 */
async function GetRedis(key) {
  try {
    const result = await Rediscli.get(key);
    if (result == null) {
      console.log("result: ", "<" + result + ">", "This key can not be found.");
      return null;
    }
    console.log("result: ", "<" + result + ">", "Get key success!...");
    return result;
  } catch (error) {
    console.log("GetRedis error is", error);
    return null;
  }
}
/**
 * 查询key是否存在
 * @param {*} key
 * @returns
 */
async function QueryRedis(key) {
  try {
    const result = await Rediscli.exists(key);
    if (result == 1) {
      console.log("result: ", "<" + result + ">", "This key is exist.");
      return true;
    }
    console.log("result: ", "<" + result + ">", "This key is not exist.");
    return false;
  } catch (error) {
    console.log("QueryRedis error is", error);
    return null;
  }
}
/**
 * 设置key和value，并设置过期时间
 * @param {*} key
 * @param {*} value
 * @param {*} expireTime
 * @returns
 */

async function SetRedisExpire(key, value, expireTime) {
  try {
    await Rediscli.set(key, value);
    await Rediscli.expire(key, expireTime);
    return true;
  } catch (error) {
    console.log("SetRedisExpire error is ", error);
    return false;
  }
}

/**
 * quit redis
 */

function QuitRedis() {
  Rediscli.quit();
}

module.exports = {
  GetRedis,
  QueryRedis,
  SetRedisExpire,
  QuitRedis,
};
