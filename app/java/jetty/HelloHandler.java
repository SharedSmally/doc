package com.jpw.app;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.handler.AbstractHandler;

public class HelloHttpRequestHandler extends AbstractHandler {
    public HelloHttpRequestHandler() {
        this("Hello World");
    }

    public HelloHttpRequestHandler( String greeting){
        this(greeting, null);
    }
    
    public HelloHttpRequestHandler( String greeting, String body ) {
        this.greeting = greeting;
        this.body = body;
    }

    @Override
    public void handle( String target, Request baseRequest,  HttpServletRequest request,
                       HttpServletResponse response ) throws IOException, ServletException
    {
        response.setContentType("text/html; charset=utf-8");
        response.setStatus(HttpServletResponse.SC_OK);

        PrintWriter out = response.getWriter();

        out.println("<h1>" + greeting + "</h1>");
        if (body != null) {
            out.println(body);
        }

        baseRequest.setHandled(true);
    }

    final String greeting;
    final String body;
}
