#include "bst.hpp"

BST::BST() {
	this->root = NULL;
}

BST::~BST() {
	deleteHelper(root);
}

void BST::deleteHelper(XPost* root)
{
	if(! root)
	{
		return;
	} else {
	deleteHelper(root->left);
	deleteHelper(root->right);
	delete root;}

}

XPost* BST::createPost(float time, string content, int likes) 
{
	XPost* post = new XPost;
	post->postedTime = time;
	post->xContents = content;
	post->likes = likes;
	post->left = nullptr;
	post->right = nullptr;
	return post;
}

void BST::insertPost(float time, string content, int likes) 
{
	XPost* post = createPost(time, content, likes);
	insertHelper(this->root,post);
}

void BST::insertHelper(XPost* &rt, XPost* pst) 
{
	
	if(! rt )
	{
		rt = pst;
		return;
	}
	
	if(pst->postedTime < rt->postedTime)
	{
		if(! rt->left)
		{
			rt->left = pst;
			return;
		}
		else{
			 insertHelper(rt->left, pst);
		}
	}
	else if(pst->postedTime > rt->postedTime)
	{
		if(! rt->right)
		{
			rt->right = pst;
			return;
		}
		else{ 
			insertHelper(rt->right, pst);
		}
	} else{
		if(! rt->left){
		pst->left = rt->left;
		rt->left = pst;
		return;}
		else{insertHelper(rt->left,pst);}
	}
}

void BST::displayPosts() 
{
	displayHelper(this->root);
}

void BST::displayHelper(XPost* rt) // Inorder Traversal
{
	if(! rt)
	{
		return;
	}
	displayHelper(rt->left);
	cout << rt->postedTime << ":\n" <<rt->xContents << endl;
	displayHelper(rt->right);
}

XPost* BST::mostPopular() 
{
	XPost* post = new XPost();
	mostPopularHelper(this->root, post);
	return post;
}

void BST::mostPopularHelper(XPost* rt, XPost*& mostLiked) 
{
	if(! rt)
	{
		return;
	}
	if(rt->likes > mostLiked->likes)
	{
		mostLiked = rt;
	}
	mostPopularHelper(rt->left, mostLiked);
	mostPopularHelper(rt->right, mostLiked);
}
