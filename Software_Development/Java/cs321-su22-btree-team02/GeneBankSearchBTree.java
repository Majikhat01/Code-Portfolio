import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class GeneBankSearchBTree {

    private static String BTreeFile;

    public static void main(String args[]) throws IOException {

        int searchCounter = 0;

        long startTime = System.currentTimeMillis();

        //Argument length must be either 3, 4, or 5
        if (!(args.length == 3 || args.length == 4 || args.length == 5)) {
            printUsageAndExit(1);
        }

        //assign arguments to variables
        int cache = Integer.parseInt(args[0]);
        BTreeFile = args[1];
        File queryFile = new File(args[2]);
        int cacheSize = 0;
        int debugLevel = 0;
        boolean useCache = false;

        //Cache choice is either 0 or 1 to signify its usage
        if (!(cache == 0 || cache == 1)) {
            printUsageAndExit("Must choose either 0 OR 1 for cache usage. ", 1);
        }

        if (cache == 1) {
            useCache = true;
            cacheSize = Integer.parseInt(args[3]);

            if(cacheSize <= 0 ) {
                printUsageAndExit("Cache size must be greater than 0.", 1);
            }

            if(args.length == 5) {
                debugLevel = Integer.parseInt(args[4]);
            }
        } else if (cache == 0 && args.length == 4) {
            debugLevel = Integer.parseInt(args[3]);
        }

        if (!(debugLevel == 1 || debugLevel == 0)) {
            printUsageAndExit("Debug level must be either 1 or 0", 1);
        }

        //initialize a btree with commandline parameters
        BTree newTree = new BTree(cacheSize, BTreeFile);

        //try to parse file
        try {

            Scanner scan = new Scanner(queryFile);

            while(scan.hasNextLine()) {
                String query = scan.nextLine();
                
                long searchKey = GeneBankCreateBTree.stringToLong(query);
                int freq = newTree.searchStart(searchKey);

                if(freq > 0) {
                    System.out.println(query.toLowerCase() +  ": " + freq);
                }

                searchCounter++;

                if (searchCounter % 100000  == 0) {
                    System.out.print(". ");
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        long endTime = System.currentTimeMillis();
//        System.out.println("\nTime: " + (endTime - startTime));
    }

    public static void printUsageAndExit(String message, int i) {
        System.out.println(message);
        System.out.println("java GeneBankSearch <0/1(no/with Cache)> <btree file> <query file> [<cache size>] [<debug level>]");
        System.exit(i);
    }

    public static void printUsageAndExit(int i) {
        System.out.println("java GeneBankSearch <0/1(no/with Cache)> <btree file> <query file> [<cache size>] [<debug level>]");
        System.exit(i);
    }
}