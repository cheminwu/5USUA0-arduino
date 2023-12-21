#include "crypto.h"
#include "MD5.h"
#include "StringSplitter.h"


String key;

void setKey(String pKey){

  key = pKey;
//   Serial.print("set key: ");
//   Serial.println(key);
}

bool verify(String content, String data[], long current_time){

  // Serial.println(content);

  StringSplitter *splitter = new StringSplitter(content, ',',6); 
  String prefix = splitter->getItemAtIndex(0);
  String requestId = splitter->getItemAtIndex(1);
  String lockerId = splitter->getItemAtIndex(2);
  String flag = splitter->getItemAtIndex(3);
  String qrTimeStr = splitter->getItemAtIndex(4);
  String sign = splitter->getItemAtIndex(5);

  char *endPtr;
  long qrTime = strtol(qrTimeStr.c_str(), &endPtr, qrTimeStr.length());
  // Serial.println(current_time);
  // Serial.println(qrTime);
  if(current_time - qrTime > 120){
    Serial.println("the code was time out.");
    return false;
  }
  String raw = requestId + "," + lockerId + "," + flag + "," + qrTimeStr + key;

//   Serial.println(raw);
  unsigned char* hash=MD5::make_hash(raw.c_str());
  char *md5str = MD5::make_digest(hash, 16);

  // Serial.println(userId);
  // Serial.println(lockerId);
  // Serial.println(flag);
  // Serial.println(qrTimeStr);
  Serial.println(sign);
  Serial.println(String(md5str));

  // Serial.println(String(md5str) == sign);
  if(String(md5str) == sign){

    data[0] = prefix;
    data[1] = requestId;
    data[2] = lockerId;
    data[3] = flag;
    data[4] = qrTimeStr;
    data[5] = sign;
    return true;
  }else{
    Serial.println("false code.");
    return false;
  }
}