import java.util.LinkedList;

public class Cache<T> {

    //Creates new linked list to act as cache
    private LinkedList<BTree.BTreeNode> list;

    int maxSize;

    public Cache(int size){

        //Set max size of linked list
        maxSize = size;

        //Create linked list to be used as cache
        list = new LinkedList<>();
        
    }

    public BTree.BTreeNode getObject(long searchKey){
        BTree.BTreeNode retNode = null;

        for (BTree.BTreeNode node : list) {
            if (node.getLocation() == searchKey) {
                return retNode = node;
            }
        }

        return retNode;
    }

    public BTree.BTreeNode getLast() {
        if (!list.isEmpty()) {
            return list.removeLast();
        } else {
            return null;
        }
    }

    public boolean isEmpty(){
        if (list.isEmpty()) {
            return true;
        } else {
            return false;
        }
    }

    public BTree.BTreeNode addObject(BTree.BTreeNode object) {
        BTree.BTreeNode retVal = null;

        if (list.size() == maxSize) {

            retVal = list.removeLast();
        }

        list.addFirst(object);
        return retVal;
    }

    public void removeObject(BTree.BTreeNode object) {
        list.remove(object);
    }

    public void moveObject(BTree.BTreeNode object) {
        removeObject(object);
        addObject(object);
    }
}
