public class trialassignment {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int lines, total;
        lines = sc.nextInt();

        int []array = new int [lines];

        for(int i=0;i<lines;i++){
            total = sc.nextInt();
            int[] numbers = new int[total - 2];

            for(int j=0;j< total - 2;j++){
                numbers[j] = sc.nextInt();
            }
            int sum = 0;
            sum += numbers[sc.nextInt()-1];
            sum += numbers[sc.nextInt()-1];
            array[i] = numbers;
        }
        for (int i=0;i<lines;i++){
            System.out.println(array[i]);
        }

    }
}
