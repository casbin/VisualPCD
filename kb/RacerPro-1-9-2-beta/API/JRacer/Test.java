
import jracer.*;
import java.io.*;

public class Test {


public static void main(String[] argv) {
    String ip = "127.0.0.1";
    int port = 8088;

    RacerServer racer1 = new RacerServer(ip,port);
    try {
	racer1.openConnection();
	System.out.println(racer1.send("(in-knowledge-base default)"));
	System.out.println(racer1.send("(define-datatype-property |age| :range integer)"));
	System.out.println(racer1.send("(implies a b)"));
	System.out.println(racer1.send("(implies b c)"));
	System.out.println(racer1.send("(implies c d)"));
	System.out.println(racer1.send("(implies d f)"));
	System.out.println(racer1.send("(instance i top)"));
	System.out.println(racer1.send("(datatype-role-filler i 42 |age|)"));
	System.out.println("Preparing Racer Engine");
	System.out.println(racer1.send("(prepare-racer-engine)"));
	System.out.println(racer1.send("(concept-parents b)"));
	System.out.println(racer1.send("(concept-parents c)"));
	System.out.println(racer1.send("(concept-parents d)"));
	System.out.println("100 (instance i_index a)");
	for(int i=0; i<100; i++) {
	    String ignore=racer1.send("(instance i"+i+" a)");
	}
	System.out.println("100000 (concept-instances top)");
	long start=System.currentTimeMillis();
	for(int i=0; i<100000; i++) {
	    String test=racer1.send("(concept-instances top)");
	}
	long end=System.currentTimeMillis();
	System.out.println("Time: "+ (end-start)/1000.0);
	}
    catch (Exception e) {
	e.printStackTrace();
    }
}
	
}