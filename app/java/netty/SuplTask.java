package com.jpw.app;

import io.netty.channel.Channel;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelFutureListener;

class SuplTask implements Runnable {
    public SuplTask(Channel channel, byte[] data) {
        this.channel = channel;
        this.data = data;
    }

    public void run()
    {
        System.out.println();

        byte[] data = Util.toByteArray(Util.SAMPLE_STR);
        System.out.println("SuplTask send data: length="+data.length);
        
        ChannelFuture future = channel.writeAndFlush(data);
        
        // Wait until all messages are flushed before closing the channel.
        if (future != null) {
            future.addListener(new ChannelFutureListener() {
                public void operationComplete(ChannelFuture channelFuture) {
                     System.out.println("SuplTask finish Sending data:");
                    // Perform post-closure operation ...
                }
            });
            
            try {
                future.sync();
            } catch (Exception ex)
            {}
        } else {
           System.out.println("SuplTask fails to write and flush data");
        }
    }

    Channel channel;
    byte[] data;
}
