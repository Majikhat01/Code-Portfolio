import java.io.*;
import java.nio.ByteBuffer;
import java.util.LinkedList;

public class BTree {

    //Offset of BTreeNode in the byteArray
    private long rootOffSet = 16;

    //Need root which is reference to byte address
    private BTreeNode root;

    //K = substring length
    private int seqLength;

    //Degree of the tree
    private int degree;

    //Potential Cache Size
    private int cacheSize;

    private long nextAddress;

    private Cache<BTreeNode> BTreeCache = null;

    //RAF to create new file to store all BTree information
    private RandomAccessFile byteFile;

    private int nodeSize = 4 + 1 + 12 * (2 * degree - 1) + 8 * (2 * degree);

    private int counter = 0;

    // class constructor
    public BTree(String fileName, int k, int t, int cacheSize, boolean useCache) throws IOException {
        byteFile = new RandomAccessFile(fileName, "rw");
        degree = t;

        if (degree == 0) {
            degree = calculateOptimumDegree();
        }

        root = new BTreeNode(rootOffSet);
        root.leaf = true;
        seqLength = k;

        this.writeMD();

        nodeSize = 4 + 1 + 12 * (2 * degree - 1) + 8 * (2 * degree);
        nextAddress = rootOffSet + nodeSize;

        if (useCache) {
            BTreeCache = new Cache<>(cacheSize);
        }
    }

    public BTree(int cacheSize, String filePath) throws IOException {
        byteFile = new RandomAccessFile(filePath, "rw");
        byteFile.seek(0);
        rootOffSet = byteFile.readLong();
        seqLength = byteFile.readInt();
        degree = byteFile.readInt();
        nodeSize = 4 + 1 + 12 * (2 * degree - 1) + 8 * (2 * degree);
        this.cacheSize = cacheSize;
        root = diskRead(rootOffSet);
    }

    public String getNodeAtIndex(int index) throws IOException {
        if (index < 1) {
            return null;
        }

        LinkedList<BTreeNode> Q = new LinkedList<>();
        Q.addFirst(root);

        for (int j= 1; j <= index - 1; j++) {
            BTreeNode node = Q.removeLast();

            if (!node.leaf) {
                for (int k = 1; k <= node.numKeys + 1; k++) {
                    BTreeNode child = diskRead(node.children[k]);
                    Q.addFirst(child);
                }
            }
        }

        BTreeNode node = Q.removeLast();
        return node.toString();
    }


    public int BTreeSearch(BTreeNode x, long k) throws IOException {
        int i = 1;

        while (i <= x.getKeys() && k > x.keys[i].getDNA()) {
            i++;
        }

        if (i <= x.getKeys() && k == x.keys[i].getDNA()) {
            return x.keys[i].getFrequency();
        } else if (x.leaf) {
            return -1;
        } else {
            if (x.children[i] == 0) {
                return -1;
            }
            BTreeNode child = diskRead(x.children[i]);
            return BTreeSearch(child, k);
        }
    }

    public int searchStart(long k) throws IOException {
       return BTreeSearch(root, k);
    }

    public void closeCache() throws IOException {
        if (BTreeCache != null) {
            while (!BTreeCache.isEmpty()) {
                BTreeNode refNode = BTreeCache.getLast();
                long address = refNode.getLocation();
                byteFile.seek(refNode.getLocation());
                byteFile.write(refNode.serialize());
            }
        }
    }

    public void BTreeInsert(long k) throws IOException {
        BTreeNode r = root;
        if (r.getKeys() == ((2 * degree) - 1)) {
            BTreeNode s = new BTreeNode(nextAddress);
            nextAddress = nextAddress + nodeSize;
            this.root = s;
            s.setLeaf(false);
            s.setKeys(0);
            s.children[1] = r.getLocation();

            BTreeSplitChild(s, 1, r);
            BTreeInsertNonfull(s, k);
        } else {
            BTreeInsertNonfull(r, k);
        }

        counter++;

        if (counter % 100000  == 0) {
            System.out.print(". ");
        }
    }

    public void BTreeInsertNonfull(BTreeNode x, long k) throws IOException {
        int i = x.numKeys;

        if (x.leaf) {

            //checks for duplicate keys before inserting
            for (int j = 1; j <= x.numKeys; j++) {
                if (k == x.keys[j].getDNA()) {
                    x.keys[j].setFrequency(x.keys[j].getFrequency() + 1);
                    diskWrite(x);
                    return;
                }
            }

            while (i >= 1 && k < x.keys[i].getDNA()) {
                x.keys[i + 1] = x.keys[i];
                i--;
            }

            x.keys[i + 1] = new TreeObject(k, 1);
            x.numKeys = x.numKeys + 1;
            diskWrite(x);
        } else {
            while (i >= 1 && k < x.keys[i].getDNA()) {
                i--;
            }

            i++;
            BTreeNode child = diskRead(x.children[i]);

            if (child.numKeys == (2 * degree) - 1) {
                BTreeSplitChild(x, i, child);

                if (k > x.keys[i].getDNA()) {
                    i++;
                }

                //update the child node to be inserted
                child = diskRead(x.children[i]);
            }

            //checks for duplicate keys before inserting
            for (int j = 1; j <= x.numKeys; j++) {
                if (k == x.keys[j].getDNA()) {
                    x.keys[j].setFrequency(x.keys[j].getFrequency() + 1);
                    diskWrite(x);
                    return;
                }
            }

            BTreeInsertNonfull(child, k);
        }
    }

    public void BTreeSplitChild(BTreeNode x, int i, BTreeNode y) throws IOException {

        BTreeNode z = new BTreeNode(nextAddress);
        nextAddress = nextAddress + nodeSize;
        z.leaf = y.leaf;
        z.setKeys(degree - 1);

        for (int j = 1; j <= degree - 1; j++) {
            z.keys[j] = y.keys[j + degree];
        }

        if (!y.leaf) {
            for (int j = 1; j <= degree; j++) {
                z.children[j] = y.children[j + degree];
            }
        }

        y.numKeys = degree - 1;

        for (int j = x.numKeys + 1; j >= i + 1; j--) {
            x.children[j + 1] = x.children[j];
        }

        x.children[i + 1] = z.location;

        for (int j = x.numKeys; j >= i; j--) {
            x.keys[j + 1] = x.keys[j];
        }

        x.keys[i] = y.keys[degree];
        x.numKeys = x.numKeys + 1;
        diskWrite(x);
        diskWrite(y);
        diskWrite(z);
    }

    public void DumpTree(BTreeNode x, PrintStream ps) throws IOException {
        if (x.isLeaf()) {
            for (int i = 1; i <= x.numKeys; i++) {
                ps.append(x.keys[i].toString(seqLength) + "\n");
            }
        } else {
            for (int i = 1; i < x.numKeys + 1; i++) {
                BTreeNode child = diskRead(x.children[i]);
                DumpTree(child, ps);
                ps.append(x.keys[i].toString(seqLength) + "\n");
            }

            DumpTree(diskRead(x.children[x.numKeys + 1]), ps);
        }
    }

    public void BTreeDump(String fileName) throws IOException {
        PrintStream ps = new PrintStream(new File(fileName));
        PrintStream Stdout = System.out;
        DumpTree(this.root, ps);
        System.setOut(ps);
        System.setOut(Stdout);
    }

    public void diskWrite(BTreeNode node) throws IOException{
        //Take a BTreeNode and serialize it and then write that information to the RAF
        if (BTreeCache != null) {
            BTreeCache.removeObject(BTreeCache.getObject(node.location));
            BTreeNode retNode = BTreeCache.addObject(node);

            if (retNode != null) {
                long address = retNode.getLocation();
                byteFile.seek(retNode.getLocation());
                byteFile.write(retNode.serialize());
            }
        } else {
            long address = node.getLocation();
            byteFile.seek(node.getLocation());
            byteFile.write(node.serialize());
        }
    }

    public BTreeNode diskRead(long nodeAddress) throws IOException {
        //Read information from the RAF and return a BTreeNode
        if (BTreeCache != null) {
            BTreeNode retNode = BTreeCache.getObject(nodeAddress);
            if (retNode == null) {
                byteFile.seek(nodeAddress);
                ByteBuffer bb = ByteBuffer.allocate(nodeSize);
                byteFile.read(bb.array());
                BTreeNode addNode = new BTreeNode(bb, nodeAddress);
                BTreeNode writeNode = BTreeCache.addObject(addNode);

                if (writeNode != null) {
                    byteFile.seek(writeNode.getLocation());
                    byteFile.write(writeNode.serialize());
                }

                return addNode;
            }

            BTreeCache.moveObject(retNode);
            return retNode;
        } else {
            byteFile.seek(nodeAddress);
            ByteBuffer bb = ByteBuffer.allocate(nodeSize);
            byteFile.read(bb.array());
            return new BTreeNode(bb, nodeAddress);
        }
    }

    public void writeMD() throws IOException {
        ByteBuffer bb = ByteBuffer.allocate(16);
        byteFile.seek((long)0);
        bb.putLong(root.location);
        bb.putInt(seqLength);
        bb.putInt(degree);
        try {
            byteFile.write(bb.array());
        } catch(IOException e) {
            System.out.println(e.toString());
        }
    }

    public int calculateOptimumDegree() {
        //NodeSize <= 4096

        int optimalDegree = (int)Math.floor(4103/40);

        return optimalDegree;
    }


    //**************** BTreeNode Start *****************
    public class BTreeNode implements Comparable<Long> {

        //Track location
        private long location;

        //# of keys
        private int numKeys;

        //check if node is a leaf
        private boolean leaf;

        private TreeObject[] keys;

        private long[] children;

        // t = degree
        public BTreeNode(long location) {
            this.location = location;
            numKeys = 0;
            leaf = false;

            keys = new TreeObject[(2 * degree)];
            children = new long[(2 * degree) + 1];
        }

        public int getKeys() {
            return numKeys;
        }

        public void setKeys(int keySize) {
             numKeys = keySize;
        }

        public long getLocation() {
            return location;
        }

        public boolean isLeaf() {
            return leaf;
        }

        public void setLeaf(boolean value) {
            leaf = value;
        }

        @Override
        public String toString() {
            String retVal = "";

            for (int i = 1; i <= this.getKeys(); i++) {
                retVal += this.keys[i].getDNA() + ", ";
            }

            return retVal;
        }

        public byte[] serialize() {
            ByteBuffer bb = ByteBuffer.allocate(4 + 1 + 12 * (2 * degree - 1) + 8 * (2 * degree));
            bb.putInt(numKeys);

            //this inputs '1111' if true and '0000' if false into bb so that
            // leaf can be either toggled on or off when reading bb.
            if (leaf) {
                bb.put((byte)15);
            } else {
                bb.put((byte)0);
            }

            for (int i = 1; i <= numKeys; i++) {
                bb.putLong(keys[i].getDNA());
                bb.putInt(keys[i].getFrequency());
            }

            for (int i = 1; i <= numKeys + 1; i++) {
                bb.putLong(children[i]);
            }

            return bb.array();
        }

        public BTreeNode(ByteBuffer bb, long location) {
            this.location=location;
            numKeys = bb.getInt();
            byte leafStatus = bb.get();
            leaf = leafStatus == 15;
            keys = new TreeObject[(2 * degree)];

            for (int i = 1; i <= numKeys; i++) {
                keys[i] = new TreeObject(bb.getLong(), bb.getInt());
            }

            children = new long[(2 * degree) +1];

            for (int i = 1; i <= numKeys + 1; i++) {
                children[i] = bb.getLong();
            }
        }

        @Override
        public int compareTo(Long o) {
            if (this.location == o) {
                return 1;
            }

            return 0;
        }
    }
}