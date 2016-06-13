public class HiLoGame
{
        static int account = 1000;
        static int bet;
        static String betLevel;
        static Scanner reader = new Scanner(System.in);
        static String numberLevel;
        public static int getRandomNumber()
        {
            return (int) (Math.random() * 13) + 1;
        }//end generate random number method
        public static void getBet()
        {
            System.out.print("Enter bet amount (enter 0 to quit): ");
            bet = reader.nextInt();
            if(bet!=0){
                System.out.print("Enter 'High' or 'Low': ");
                betLevel = reader.next();
            }
        }
        public static void getNumberLevel()
        {
            int number = getRandomNumber();
            if(number<=6){
                numberLevel = "Low";
            }else if(number>=8){
                numberLevel = "High";
            }
        }
        public static void checkBet()
        {
            getBet();
            if(numberLevel!=betLevel){
                account-=bet;
                System.out.println("Incorrect.  You lost "+bet+" dollars.");
            }else if(numberLevel==betLevel){
                account=account+(bet*2);
                System.out.println("Correct.  You won "+bet+" dollars.");
            }else{
                account-=500;
                System.out.println("Unlucky number.  You lost 500 dollars.");
            }
            if(account>0){
                System.out.println("New account balance: "+account+".");
            }
        }
        public static void main(String[] args)
        {
            getBet();
            while(account>0&&bet!=0){
                getRandomNumber();
                getNumberLevel();
                checkBet();
            }
            if(bet==0){
                System.out.println("Game Over.  Your score was "+account+".");
            }else if(account==5000){
                System.out.println("You won.  Your score exceeded the limit of 5000 (final score was "+account+".");
            }else{
                System.out.println("Game Over.  You ran out of money.");
            }
        }//end main
}//end class