#include <iostream>
#include <stack>
#include <string>
#include <cctype>

class ExpressionTree {
private:
    struct Node {
        std::string data;
        Node* left, *right;

        Node(std::string data) {
            this->data = data;
            this->left = this->right = NULL;
        };

        Node(std::string data, Node* left, Node* right) {
            this->data = data;
            this->left = left;
            this->right = right;
        };
    };

    Node* root;

public:
    ExpressionTree(std::string postfix) {
        root = construct(postfix);
    }

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

    Node* construct(std::string postfix) {
        std::stack<Node*> s;

        for (int i = 0; i < postfix.length(); ++i) {
            char c = postfix[i];
            if (isOperator(c)) {
                Node* x = s.top();
                s.pop();
                Node* y = s.top();
                s.pop();
                Node* node = new Node(std::string(1, c), y, x);
                s.push(node);
            } else if (std::isdigit(c)) {
                int numStart = i;
                while (i < postfix.length() && (std::isdigit(postfix[i]) || postfix[i] == '.')) {
                    i++;
                }
                std::string numStr = postfix.substr(numStart, i - numStart);
                i--;

                s.push(new Node(numStr));
            }
        }

        return s.top();
    }

    void preOrder(Node* root) {
        if (root == NULL) {
            return;
        }
        std::cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    void inOrder(Node* root) {
        if (root == NULL) {
            return;
        }
        inOrder(root->left);
        std::cout << root->data << " ";
        inOrder(root->right);
    }

    void postOrder(Node* root) {
        if (root == NULL) {
            return;
        }
        postOrder(root->left);
        postOrder(root->right);
        std::cout << root->data << " ";
    }

    void preOrden() {
        preOrder(root);
        std::cout << std::endl;
    }

    void inOrden() {
        inOrder(root);
        std::cout << std::endl;
    }

    void postOrden() {
        postOrder(root);
        std::cout << std::endl;
    }
};

int main() {
    //std::string postfixExpression = "3 2 + 12 - 2  ^  4  6 *  + ";
    std::string postfixExpression = "4 15 2 / 3 ^ * 5 6 5 / - /";

    ExpressionTree tree(postfixExpression);

    std::cout << "Preorden: ";
    tree.preOrden();

    std::cout << "Inorden: ";
    tree.inOrden();

    std::cout << "Postorden: ";
    tree.postOrden();

    return 0;
}
