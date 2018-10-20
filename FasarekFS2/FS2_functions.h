typedef unsigned char byte;

#ifndef HASHMAP_H
#define HASHMAP_H

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    int i;
    for (i = 0; i < sizeof(value); i++)
    EEPROM.put(ee++, *p++);
    EEPROM.commit();
    return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    int i;
    for (i = 0; i < sizeof(value); i++)
    *p++ = EEPROM.read(ee++);
    return i;
}

/*
|| @file HashMap.h
|| @version 1.0 Beta
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | This library provides a simple interface for storing data with an associate key
*/
/* Handle association */
template<typename hash,typename map>
class HashType {
public:
  HashType(){ reset(); }
  
  HashType(hash code,map value):hashCode(code),mappedValue(value){}
  
  void reset(){ hashCode = 0; mappedValue = 0; }
  hash getHash(){ return hashCode; }
  void setHash(hash code){ hashCode = code; }
  map getValue(){ return mappedValue; }
  void setValue(map value){ mappedValue = value; }
  
  HashType& operator()(hash code, map value){
    setHash( code );
    setValue( value );
  }
private:
  hash hashCode;
  map mappedValue;
};

/*
Handle indexing and searches
TODO - extend API
*/
template<typename hash,typename map>
class HashMap {
public:
  HashMap(HashType<hash,map>* newMap,byte newSize){
    hashMap = newMap;
    size = newSize;
    for (byte i=0; i<size; i++){
      hashMap[i].reset();
    }
  }
  
  HashType<hash,map>& operator[](int x){
    //TODO - bounds
    return hashMap[x];
  }
  
  byte getIndexOf( hash key ){
    for (byte i=0; i<size; i++){
      if (hashMap[i].getHash()==key){
        return i;
      }
    }
  }
  map getValueOf( hash key ){
    for (byte i=0; i<size; i++){
      if (hashMap[i].getHash()==key){
        return hashMap[i].getValue();
      }
    }
  }
  
  void debug(){
    for (byte i=0; i<size; i++){
      Serial.print(hashMap[i].getHash());
      Serial.print(" - ");
      Serial.println(hashMap[i].getValue());
    }
  }

private:
  HashType<hash,map>* hashMap;
  byte size;
};

#endif
