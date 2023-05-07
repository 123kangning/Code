class Solution:
    def getBinaryTrees(self , preOrder , inOrder ):
        if preOrder == inOrder == []: return [-1]
        res = []; root = preOrder[0]
        for i in range(len(inOrder)):
            if inOrder[i] == root:
                leftInOrder, rightInOrder = inOrder[:i], inOrder[i+1:]
                leftPreOrder, rightPreOrder = preOrder[1:i+1], preOrder[i+1:]
                leftChildren = self.getBinaryTrees(leftPreOrder, leftInOrder)
                rightChildren = self.getBinaryTrees(rightPreOrder, rightInOrder)
                for leftChild in leftChildren:
                    for rightChild in rightChildren:
                        root_node = ListNode(root)
                        root_node.left = leftChild if leftChild != -1 else None
                        root_node.right = rightChild if rightChild != -1 else None
                        res.append(root_node)
        return res

        