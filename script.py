#!/usr/bin/python
import sys  
import os

def main(): 
	filepath = str(sys.argv[1])
	print("<?xml version=\"1.0\"?>")
	with open(filepath) as fp:  
		line = fp.readline()
		cnt = 1
		while line:
			line = line.replace("\n", "")
			words = line.split(" ")
			if (not words[0].startswith('#') and line.strip()):
				if (len(words) > 1 and words[1].startswith('{')):
					tmp = words[0]
					print("<" + words[0] + ">")
				elif (words[0].startswith('}')):
					print("</" + tmp + ">")
				else:
					i = 1
					my_str = ""
					while i < len(words):
						my_str += words[i] + " "
						i += 1
					my_str.replace("\n", " ")
					print("	<" + words[0] + "> " + my_str + "</" + words[0] + ">")
			line = fp.readline()
			cnt += 1

if __name__ == '__main__':  
	main()