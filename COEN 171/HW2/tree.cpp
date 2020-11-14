#include <iostream>

using namespace std;

template <class T>
class Node{
	private:
		T value;
		Node<T> *left;
		Node<T> *right;

	public:
		//initialization
		Node(const T anobject){
			this->value = anobject;
			left = NULL;
			right = NULL;
		}

		//manipulation
		bool member(const T anobject){
			if (anobject < value){
				if (left == NULL){
					return false;
				} else {
					return left->member(anobject);
				}
			}
			if (anobject > value){
				if (right == NULL){
					return false;
				} else {
					return right->member(anobject);
				}
			}
			return true;
		}

		void insert(T anobject){
			if (anobject < value)
				if (left == NULL)
					left = new Node<T>(anobject);
				else
					left->insert(anobject);
			if (anobject > value)
				if (right ==  NULL)
					right = new Node<T>(anobject);
				else
					right->insert(anobject);
		}
};

template<class T>
class Tree{
	private:
		Node<T> *root;

	public:
		
		Tree(){
			root = NULL;
		}

		//manipulation
		bool member(T anobject){
			if (root == NULL)
				return false;
			else 
				return root->member(anobject);
		}

		void insert(T anobject){
			if (root == NULL)
				root = new Node<T>(anobject);
			else
				root->insert(anobject);
		}
};




int main(){
	Tree<int> *t;
	t = new Tree<int>();
	
	t->insert(15);
	t->insert(10);
	t->insert(20);
	t->insert(5);
	t->insert(30);
	t->insert(25);
	
	cout << t->member(15) << endl;
	cout << t->member(5) << endl;
	cout << t->member(25) << endl;
	cout << t->member(7) << endl;
	cout << t->member(11) << endl;
	cout << t->member(44) << endl;

	return 0;
}
