import java.util.Scanner;

public class cmsc401 {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner sc=new Scanner(System.in);

        int sz=sc.nextInt();

        while(sz<1 ||sz>1000000) {
            sz=sc.nextInt();
        }

        int[] numArray=new int[sz];

        for(int i=0;i<sz;i++) {
            numArray[i]=sc.nextInt();
        }

        int ctr=1;
        int me=numArray[0];

        for(int i=1;i<sz;i++) {
            if(numArray[i]==me) {
                ctr++;
            }
            else {
                ctr--;
                if(ctr==0) {
                    me=numArray[i];
                    ctr++;
                }
            }
        }
        if(ctr==0 || ctr<sz/2) {
            System.out.println("-1");
        } 
        else {
            System.out.println(me);
        }
    }
}