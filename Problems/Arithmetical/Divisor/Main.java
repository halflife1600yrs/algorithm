import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    static boolean[] sieve=new boolean[300];
    static BigInteger[] multi=new BigInteger[100];
    static BigInteger[] up=new BigInteger[100];
    static BigInteger[] down=new BigInteger[100];
    static int[] pri=new int[100];
    static int pn=0;
    final static void init() {
        for(int i=2;i<300;++i) {
            if(sieve[i]==false) {
                pri[pn++]=i;
                // System.out.println(i);
            }
            for(int j=0;j<pn&&i*pri[j]<300;++j) {
                sieve[i*pri[j]]=true;
                if(i%pri[j]==0) break;
            }
        }
    }
    final public static void main(String[] argv) throws Exception {
        init();
        multi[1]=new BigInteger("1");
        up[1]=new BigInteger("1");
        down[1]=new BigInteger("1");
        for(int i=2;i<pn;++i) {
            BigInteger tmp=new BigInteger(""+pri[i-2]);
            multi[i]=multi[i-1].multiply(tmp);
            // System.out.println("multi[i]="+multi[i].toString());
            up[i]=up[i-1].multiply(tmp);
            down[i]=down[i-1].multiply(new BigInteger(""+(pri[i-2]+1)));
            BigInteger gcd=up[i].gcd(down[i]);
            up[i]=up[i].divide(gcd);
            down[i]=down[i].divide(gcd);
            // System.out.println("up[i]="+up[i].toString());
            // System.out.println("down[i]="+down[i].toString());
        }
        Scanner cin=new Scanner(System.in);
        int t=cin.nextInt();
        int pos=1;
        for(int T=0;T<t;++T) {
            String str=cin.next();
            BigInteger n=new BigInteger(str);
            for(int i=2;i<pn;++i) {
                if(n.compareTo(multi[i])<0) {
                    pos=i-1;
                    break;
                }
            }
            System.out.println(up[pos].toString()+'/'+down[pos].toString());
        }
    }
}

/*==================================================================
added at 2019-07-11 15:10:53 gym102028F 2018icpc焦作E
打表找的规律,up[i]/down[i]=up[i-1]/down[i-1]*p[i]/(p[i]+1)
==================================================================*/