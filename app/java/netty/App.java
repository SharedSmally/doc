package com.jpw.app;

public class App {
    public static void main( String[] args ) {
        SuplServer app = new SuplServer();
        try {
            app.run(9999);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
