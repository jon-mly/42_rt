#!/usr/bin/python
import sys  
import os

def printTheme(lines):
	didParseTheme = False
	didParsePower = False
	linesToRemove = []
	
	for line in lines:
		lineIndex = lines.index(line)
		line = line.replace("\n", "")
		line = line.strip()
		if (line.startswith("theme") and not didParseTheme) or (line.startswith("power") and not didParsePower):
			if line.startswith("theme"):
				didParseTheme = True
			elif line.startswith("power"):
				didParsePower = True
			linesToRemove.append(lineIndex)
			myStr = ""
			line = line.split(" ")
			for word in line[1:]:
				myStr += word + " "
			print("<" + line[0] + "> " + myStr + "</" + line[0] + ">")
	for index in reversed(linesToRemove):
		lines.pop(index)
	return (lines)

def main(): 
	filepath = str(sys.argv[1])
	print("<?xml version=\"1.0\"?>")
	with open(filepath) as fp:
		line = fp.readline()
		lines = []
		while line:
			lines.append(line)
			line = fp.readline() 
		lines = printTheme(lines)
		cnt = 1
		for line in lines:
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
                                        if not my_str:
                                            my_str = "1 ";
					print("	<" + words[0] + "> " + my_str + "</" + words[0] + ">")
			cnt += 1

if __name__ == '__main__':  
	main()
