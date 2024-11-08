import java.net.*;
import java.io.BufferedReader;
import java.io.*;
class Client{
    public static void main(String[] args) throws Exception
    {
        Socket stk = new Socket("localhost",2000);
        BufferedReader keyb = new BufferedReader(new InputStreamReader(System.in));
        BufferedReader br = new BufferedReader(new InputStreamReader(stk.getInputStream()));
        PrintStream ps = new PrintStream(stk.getOutputStream());
        String msg;
        // StringBuilder sb;
        do
        {
            System.out.println("Enter the Message: ");
            msg = keyb.readLine();
            ps.println(msg);
            msg = br.readLine();
            System.out.println("From Server"+msg);
        }while(!msg.equals("dne"));    
        stk.close();
    }
    
}
public class ReverseEcho {  
    public static void main(String[] args) throws Exception
    {
        ServerSocket ss = new ServerSocket(2000);
        Socket stk = ss.accept();
        BufferedReader br = new BufferedReader(new InputStreamReader(stk.getInputStream()));
        PrintStream ps = new PrintStream(stk.getOutputStream());
        System.out.println("Server has started");
        String msg;
        do 
        {
            msg = br.readLine();
            StringBuilder sb = new StringBuilder(msg);
            // sb.reverse();
            msg = sb.toString();
            ps.println(msg);
        }while(!msg.equals("dne"));

    }
}