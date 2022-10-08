// Flatten binary tree to linked list GFG

class Solution
{
    public:
    void flatten(Node *root)
    {
        //code here
        if(root){
            
            //Move the left node to the right node
            Node* temp = root->right;
            root->right = root->left;
            root->left = NULL;
            Node* node = root;
            
            // Move to the end of the prev left node 
            // which is the new right node
            while(node->right){
                node = node->right;
            }
            
            //Append the right node to it's end
            node->right = temp;
            flatten(root->right);
        }
        return;
    }
};
