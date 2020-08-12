package com.jpw.app;

import io.netty.buffer.ByteBuf;
import javax.xml.bind.DatatypeConverter;

class Util {
    static final String SAMPLE_STR= "003B020000C000009014000003FFFFFC0000000405102B101400047D1241000800D62E183166C59306AC9935B4E9DD10F3C2507428005A002D0800";

    public static String hex(ByteBuf buf) {
        StringBuilder result = new StringBuilder();
        
        for (int i = 0; i < buf.readableBytes(); i ++) {
            byte b = buf.getByte(i);
            result.append(String.format("%02x", b));
            // result.append(String.format("%02X", aByte)); // upper case
        }
        
        return result.toString();
    }
    
    public static String toHexString(byte[] array) {
        return DatatypeConverter.printHexBinary(array);
    }

    public static byte[] toByteArray(String s) {
        return DatatypeConverter.parseHexBinary(s);
    }    
}
