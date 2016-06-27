from collections import deque

def parser(string1, tree_dict):
	start = 0
	root = None
	prev = None
	lst1 = []
	for i in range (0, len(string1)):
		if string1[i] == ' ':
			print tree_dict
			topic = string1[start: i]
			if topic == '(':
				if len(tree_dict[prev]) > 0:
					prev = tree_dict[prev][-1]
					lst1.append(prev)
				start = i+1
				continue
			if topic == ')':
				del lst1[-1]
				if len(lst1) > 0:
					prev = lst1[-1]
				start = i+1
				continue

			if root == None:
				root = topic
				tree_dict[topic]= []
				prev = root
				lst1.append(root)		
			else:
				tree_dict[topic] = []
				tree_dict[prev].append(topic)
			start = i+1 
	return tree_dict


def main():
	string1 = "Animals ( Reptiles Birds ( Eagles Pigeons Crows ) )"
	tree_dict = {}
	tree_dict = parser(string1, tree_dict)	
	print tree_dict

main()	
