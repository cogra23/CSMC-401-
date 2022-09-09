import java.util.*; // Code by Colin Graham 8/26/22
public class csmc401 
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);

        int lines, total, i, j;
        lines = sc.nextInt();

        int []arr_sum = new int [lines];

        for(i=0;i<lines;i++)
        {
            total = sc.nextInt();
            int[] numbers_array = new int[total - 2];

            for(j=0;j< total-2;j++){
                numbers_array[j] = sc.nextInt();
            }
            int numbers_sum = 0;
            numbers_sum += numbers_array[sc.nextInt()-1];
            numbers_sum += numbers_array[sc.nextInt()-1];
            arr_sum[i] = numbers_sum;
        }
        for (i=0;i<lines;i++){
            System.out.println(arr_sum[i]);
        }

    }
}


