import java.io.Console;
import java.util.Stack;
import java.math.*;

public class Hanoi
{
    static peg l;
    static peg c;
    static peg r;
    static int n = 32;
    static int o = 0;
    static double a = 0;

    public static void main(String[] args) 
    {

        for(int i = 27; i < 40; i++)
        {
            n = i;
            
            System.out.println("-------------");
            System.out.println("Solving for n = " + n);
            l = new peg(n, true);
            c = new peg(n, false);
            r = new peg(n, false);
            Double moves = Math.pow(2, n)-1;
            long currMillis = System.currentTimeMillis();
            System.out.println("(Moves: " + moves + ")");
            System.out.println("Predicted Time: " + (2+o*0.2)* a * moves + "ms");
            Shift(l,r,c,n);
            long solveMillis = System.currentTimeMillis();
            long delta = solveMillis - currMillis;
            System.out.println("Solved " + n + " disks in " + delta + "ms");
            System.out.println("(avg: " + delta/moves + "ms per step)");
            a = (a+(delta/moves))/(++o);



        }

    }    

    public static void ascii()
    {
        String ins = "  ";
        for(int i = 0; i < n;i++)
        ins = ins + "      ";

        for(int i = 0; i < n;i++)
        {
            StringBuilder sb = new StringBuilder(ins);
            sb.setCharAt(2*n, ' ');
            sb.setCharAt(n*4+1,' ');
            
            int ll = l.dat[n-i-1];
            int cc = c.dat[n-i-1];
            int rr = r.dat[n-i-1];

            for(int k = 0; k < ll; k++)
            {
            sb.setCharAt(n-1-k, '/');
            sb.setCharAt(n+k, '\\');
            }

            for(int k = 0; k < cc; k++)
            {
            sb.setCharAt(n*3-k, '/');
            sb.setCharAt(n*3+k+1, '\\');
            }

            for(int k = 0; k < rr; k++)
            {
            sb.setCharAt(n*5-k+1, '/');
            sb.setCharAt(n*5+k+2, '\\');
            }
            System.out.println(sb.toString());
        }

    }

    public static void Shift(peg from, peg to, peg using, int k)
    {
        if(k == 0)
        return;
        Shift(from,using,to,k-1);
        to.pull(from);
        Shift(using,to,from,k-1);
    }

}   
class peg extends Stack
{
    public int[] dat;
    public int ind = -1;

    public peg(int n, boolean fill)
    {
        dat = new int[n];
        if(fill)
        for(int i = 0; i < n; i++)
        push(n-i);
    }

    public void print()
    {
        int k = 0;
        for (int i : dat)
        System.out.println("Layer " + k++ + ": " + i);
    }

    @Override
    public Object pop()
    {
        int ret = dat[ind];
        dat[ind] = 0;
        ind--;
        return ret;
    }
    @Override
    public Object push(Object e)
    {
        dat[++ind] = (int)e;
        return e;
    }
    @Override
    public Object peek() 
    {
        return dat[ind];        
    }

    public void pushTo(peg p)
    {
        p.push(pop());
    }
    public int pull(peg p)
    {
        return (int)push(p.pop());
    }
}