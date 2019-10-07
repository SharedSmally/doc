//https://github.com/redis/hiredis: sync api
#include "hiredis.h"

void test1(redisContext *c)
{
	printf("redis test1");
	redisReply *reply;

	//redisvCommand();
	reply = (redisReply *) redisCommand(c,"SET %s %s","foo","hello, this is the test bar");
	freeReplyObject(reply);

	reply = (redisReply *) redisCommand(c,"GET %s","foo");
	printf("%s\n",reply->str);
	freeReplyObject(reply);
}

//redisGetReplyXXX in non-blocking mode
void test2(redisContext *context)
{
	printf("redis test2\n");
	redisReply *reply;
	redisAppendCommand(context,"SET testfoo %s", "this is testfoo");
	redisAppendCommand(context,"GET testfoo");

	redisGetReply(context,(void **)&reply); // reply for SET
	//printf("type=%n",reply->type);
	freeReplyObject(reply);

	redisGetReply(context,(void **)&reply); // reply for GET
	printf("Get %s\n",reply->str);
	freeReplyObject(reply);
}

int main()
{
	redisContext *c = redisConnect("localhost", 6379); //redisConnectXXX; not support SSL, use stunnel instead
	if (c != NULL && c->err) {
	    printf("Error: %s\n", c->errstr);
	    // handle error
	} else {
	    printf("Connected to Redis\n");
	}

    test1(c);

    test2(c);

	redisFree(c);  //redisFreeXXX
}
