from collections import deque
class Node:
	def __init__(self):
		self.children = {}
		self.count = 0

class Trie:
	def __init__(self):
		self.root = Node()
	
	def insert(self, trie_dict, c):
		if c in trie_dict.children:
			trie_dict.children[c].count += 1
		else:
			trie_dict.children[c] = Node()
			trie_dict.children[c].count = 1 
		return trie_dict.children[c]

	def insert_helper(self, question):
		current = self.root 
		for chr in question:
			current = self.insert(current, chr)

	
	def query(self, question):
		current = self.root
		for chr in question:
			if chr not in current.children:
				return 0
			current = current.children[chr]
		return current.count

class TreeNode:
	def __init__(self):
		self.trie = Trie()
		self.children = []

class NaryTree:
	def __init__(self):
		self.tree_dict = {}

	def add_node(self, parent, child):
		if parent not in self.tree_dict:
			self.tree_dict[parent] = TreeNode()
		self.tree_dict[parent].children += child
		

	def sentence_append(self, question, node):
		self.tree_dict[node].trie.insert_helper(question)

	def query(self, question, node):
		return self.tree_dict[node].trie.query(question)
	
	def printtree(self):
		for key in self.tree_dict:
			print key,
			print self.tree_dict[key].children

def save_questions(_tree, question_string):
	topic, question = question_string.split(":")
	_tree.sentence_append(question.strip(), topic.strip())

def bfs_query_count(_tree, sentence):
	parsed = sentence.split(' ',1)
	q = deque()
	q.append(parsed[0])
	result = 0
	while len(q) > 0:
		c = q.popleft()
		q.extend(_tree.tree_dict[c].children)
		result += _tree.query(parsed[1],c)
	return result


def tree_parser(tree_string, _tree):
	start = 0
	root = None
	prev = None
	children = []
	for i in range(0, len(tree_string)):
		if tree_string[i] == ' ':
			topic = str(tree_string[start:i])
			if topic == '(':
				if len(_tree.tree_dict[prev].children) > 0:
					prev = _tree.tree_dict[prev].children[- 1 ]
					children.append(prev)
				start = i+1
				continue
			if topic == ')':
				del children[-1]
				if len(children) > 0:
					prev = children[-1]
				start = i+1
				continue
			if root == None:
				root = topic
				_tree.add_node(root, [])
				prev = root
				children.append(root)
			else:
				_tree.add_node(topic,[])
				_tree.add_node(prev, [topic])
			start = i+1	
	return _tree

def main():
	_tree = NaryTree()
	tree_size = int(raw_input())
	tree_string = raw_input()
	_tree = tree_parser(tree_string, _tree)
	
	topic_question_count = int(raw_input())
	for i in range(0,topic_question_count):
		save_questions(_tree, raw_input())
	
	query_count = int(raw_input())
	for i in range(0,query_count):
		print bfs_query_count(_tree, raw_input())
	
main()	
