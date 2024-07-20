import com.sun.source.tree.Tree;

public class TreeObject {

    //Substring of DNA
    private long DNA;

    //Frequency of character substring that appears in DNA
    private int frequency;

    public void incrementFrequency() {
        frequency ++;
    }

    public int getFrequency() {
        return frequency;
    }

    public int setFrequency(int newFrequency) {
        return frequency = newFrequency;
    }

    public TreeObject(long startDNA, int newFrequency) {
        DNA = startDNA;
        frequency = newFrequency;
    }

    public long getDNA() {
        return DNA;
    }

    public String toString(int sequenceLength) {
        int k = sequenceLength;
        String stringDNA = Long.toBinaryString(DNA);
        StringBuilder returnDNA = new StringBuilder();

        while (stringDNA.length() < sequenceLength * 2) {
            stringDNA = "0".concat(stringDNA);
        }

        for (int i = 0; i < stringDNA.length(); i += 2) {
            String singleDNA = stringDNA.substring(i, i+2);

            switch (singleDNA) {
                case "00": returnDNA.append("a");
                    break;
                case "11": returnDNA.append("t");
                    break;
                case "01": returnDNA.append("c");
                    break;
                case "10": returnDNA.append("g");
                    break;
            }
        }

        return  returnDNA + ": " + frequency;
    }
}