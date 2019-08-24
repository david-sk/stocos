#!/usr/bin/env python
#-*- coding: utf-8 -*-
# Python 3.7

#
# @Author: Jxtopher
# @License: CC-BY-NC-SA
# @Date: 2018
# @Version: v2
# @Purpose: *
#

from itertools import cycle
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import json
#matplotlib.style.use('ggplot')


class Plot:
	def __init__(self, width = 5, height = 5, margins = 0.05):
		fig, ax = plt.subplots(figsize=(width, height))
		ax.margins(margins)

		# Colors, markers and lines
		self.lines = ["-"]#,"--","-.",":"]
		self.markers = ["o", "v", "^", "^", ">", "1", "2", "3", "4", "8", "s", "p", "*", "h", "H", "+", "<", "D"]
		self.colors = ["black", "blue", "green", "red", "brown", "magenta", "silver", "pink"]
		self.linecycler = cycle(self.lines)
		self.markercycler = cycle(self.markers)
		self.colorcycler = cycle(self.colors)

	def auto(self):
		return NotImplemented

	def legend(self, xlabel = "", ylabel = "",  title = "", legend="inside", size = "large"):#"medium"):
		if ylabel != "":
			plt.ylabel(ylabel, fontsize=size)
		if xlabel != "":
			plt.xlabel(xlabel, fontsize=size)
		if title != "":
			plt.title(title)

		plt.grid(True)

		if legend == "inside":
			plt.legend(loc="best",prop={'size':size})
		elif legend == "outside":
			plt.legend(loc='center left', bbox_to_anchor=(1, 0.5),prop={'size':size}) #(loc='upper center', ncol=3, fancybox=True)

	def lim(self, xlim_min, xlim_max, ylim_min, ylim_max):
		plt.xlim([xlim_min, xlim_max])
		plt.ylim([ylim_min, ylim_max])

	def tofile(self, outfile = "output.pdf"):
		plt.savefig(outfile, bbox_inches='tight')

	def scale(self, xscale = u'linear', yscale = u'linear'):
		plt.xscale(xscale) # plt.yscale('log')
		plt.yscale(yscale) #plt.xscale('log')

class Boxplot(Plot):
	def __init__(self):
		Plot.__init__(self, 5, 5, 0.05)
		print ("Boxplot(Plot)")

	def boxplot(self, data, xticks = [], verticalBox=True):
		if verticalBox == True:
			plot1 = plt.boxplot(data, widths=0.7, patch_artist=True)
			plt.xticks(rotation=90)
			if (xticks != []):
				plt.xticks(range(1, len(xticks)+1), xticks)
		else:
			plot1 = plt.boxplot(data, widths=0.7, patch_artist=True, vert=False)

			if (xticks != []):
				plt.yticks(range(1, len(xticks)+1), xticks)

		plt.setp(plot1['boxes'], linewidth=1.5, facecolor='SkyBlue')#color='Black',  linewidth=1.5, facecolor='SkyBlue')

	def auto(self, data, xticks = [], outfile = "output.pdf", xlabel = "", ylabel = "", title = "", verticalBox=True):
		self.boxplot(data, xticks, verticalBox)
		self.legend(xlabel, ylabel, title, legend="", size = 16)
		self.tofile(outfile)
		#toCSV(data, xticks, outfile +".csv")

class Linesplot(Plot):
	def __init__(self):
		Plot.__init__(self, 5, 5, 0.05)
		print ("Linesplot")
		self.datax = []
		self.datay = []
		self.datae = []
		self.datalabel = []

	def add(self, data : dict, name_x : str = "x", name_y : str = "y", name_e : str = "e", label = "", line = True, marker = True, size = 1):
		x : list = []
		y : list = []
		e : list = []
		for d in data:
			x.append(d[name_x])
			y.append(d[name_y])
			if name_e in d:
				e.append(d[name_e])
		if len(e) == 0:
			e = None
		self.add_curve(x, y, e, label, line, marker, size)

	# x : liste du jeu de donnees en x
	# y : liste du jeu de donnees en y
	# e : liste du jeu de donnees pour la barre d'erreur
	# size : taille markersize et linewidth
	def add_multiCurve(self, x, y, e = None, label = [], line = True, marker= True, size = 1):
		if len(y) != len(x) :
			print("WARNING: len(y) != len(x) ")
		if e != None and len(y) != len(e) :
			print("WARNING: len(y) != len(e) ")

		for i in range(0, len(y)) :
			if e != None:
				self.add_curve(x[i], y[i], e[i], label[i], line, marker, size)
			else:
				self.add_curve(x[i], y[i], None, label[i], line, marker, size)

	# x : liste du jeu de donnees en x
	# y : liste du jeu de donnees en y
	# e : liste du jeu de donnees pour la barre d'erreur
	# size : taille markersize et linewidth
	def add_curve(self, x, y, e = None, label = "", line = True, marker = True, size = 1):
		self.datax += [x]
		self.datay += [y]
		self.datae += [e]
		self.datalabel += [label]

		if e == None :
			if line and marker:
				plt.plot(x, y, linestyle=next(self.linecycler), marker=next(self.markercycler), label=label, linewidth=size, markersize=(size*5), markeredgewidth=0.0, color=next(self.colorcycler))
			elif line:
				plt.plot(x, y, linestyle=next(self.linecycler), label=label, linewidth=size, markeredgewidth=0.0, color=next(self.colorcycler))
			elif marker:
				plt.plot(x, y, linestyle='None', marker=next(self.markercycler), label=label, markersize=size, markeredgewidth=0.0, color=next(self.colorcycler))
			else:
				plt.plot(x, y, linestyle='None', label=label, markeredgewidth=0.0, color=next(self.colorcycler))

		else :
			if line and marker:
				plt.errorbar(x, y, e, linestyle=next(self.linecycler), marker=next(self.markercycler), label=label, linewidth=size, markersize=size * 5, markeredgewidth=0.0, color=next(self.colorcycler))
			elif line:
				plt.errorbar(x, y, e, linestyle=next(self.linecycler), label=label, linewidth=size, markeredgewidth=0.0, color=next(self.colorcycler))
			elif marker:
				plt.errorbar(x, y, e, linestyle='None',  marker=next(self.markercycler), label=label, markersize=size, markeredgewidth=0.0, color=next(self.colorcycler))
			else:
				plt.errorbar(x, y, e, linestyle='None', label=label, markeredgewidth=0.0, color=next(self.colorcycler))

	# marker : True|False resp. marker | aucune marker
	# legend : inside|outside
	# size : taille markersize et linewidth
	def auto(self, x, y, e = None, label = [], outfile = "output.pdf", xlabel = "", ylabel = "", title = "", legend="inside", line = True, marker= True, size = 1):
		self.add_multiCurve(x, y, e, label, line, marker, size)
		self.legend(xlabel, ylabel, title, legend)
		self.tofile(outfile)

class Scatter(Plot):
	def __init__(self):
		Plot.__init__(self, 5, 5, 0.05)

	#def add_sample()

	def auto(self, x, y, colors, outfile = "output.pdf", marker_size = 200, marker = "s", xlabel = "", ylabel = "",  barlabel = "", title = ""):
		scat = plt.scatter(x, y, marker = next(self.markercycler), s=marker_size, c=colors, alpha=0.8, edgecolors='none')
		cbar = plt.colorbar(scat)

		self.legend(xlabel, ylabel, title)
		self.tofile(outfile)

class Contour2d(Plot):
	def __init__(self):
		Plot.__init__(self, 5, 5, 0)

	def auto(self, x, y, z, outfile = "output.pdf", xlabel = "", ylabel = "",  barlabel = "", title = ""):
		cf = plt.contourf(x, y, z, 40)
		cbar = plt.colorbar(cf)
	#	cbar.ax.set_ylabel('Energy (eV)')
		cbar.ax.set_ylabel(barlabel)
		#plt.contourf(x, range(len(y)), z
	#	plt.yticks(range(len(y)), y=y)#, color='red')

		self.legend(xlabel, ylabel, title)
		self.tofile(outfile)

class histogram(Plot):
		def __init__(self):
			Plot.__init__(self, 5, 5, 0)

		# a		: array or sequence of (n,) arrays
		# normed	: normalized to form a probability density,
		# bins		: integer or array_like, optional
		def auto(self, a, label = [], outfile = "output.pdf", xlabel = "", ylabel = "",  title = "", legend="inside", density=False, bins = 10):
			plt.hist(a, label=label, bins=bins, density=density)#, bins=[0, 1, 2, 3])
			self.legend(xlabel, ylabel, title, legend)
			self.tofile(outfile)
			#plt.savefig(outfile, bbox_inches='tight')

"""
if __name__ == '__main__':
	#data = [
	#	[1, 3, 4, 5],			# A
	#	[10, 10, 11, 19],		# B
	#	[2, 3, 1, 4, 5, 1],		# C
	#	[2, 4]					# D
	#]

	#name = ["A", "B", "C", "D"]
	#boxplotx = Boxplot()
	#boxplotx.auto(data,  name, outfile = "output.pdf")
	#boxplotx = Boxplot()
	#boxplotx.auto(data, name, outfile = "output1.pdf", verticalBox = False)

	x1 = [0, 1, 2, 3, 4, 5, 6]
	y1 = [10, 5, 4, 2, 1, 0, -1]
	e1 = [2, 2, 2, 2, 2, 2, 2]

 	x2 = [0, 1, 2, 3, 4, 5, 6]
	y2 = [0, 15, 14, 12, 11, 10, 1]

	p = Linesplot()
	p.auto(x = [x1, x2], e = [e1, None], y = [y1, y2], label = ["a", "b"], xlabel = ur"$x_é$", ylabel = ur"$y_à$", outfile = "toto.pdf")

	x1 = [0, 1, 2, 3, 4, 5, 6]
	y1 = [10, 5, 4, 2, 1, 0, -1]
	c1 = [0, 1, 2, 3, 4, 5, 6]
	p = Scatter()
	p.auto(x1, y1 , c1 , outfile = "output.pdf")

	x1 = [0, 1, 2]
	y1 = [0, 1, 2]
	z1 = [[1, 1, 1], [1, 2, 1] ,[1, 1, 1]]
	p = Contour2d()
	p.auto(x = x1, y = y1, z = z1, outfile = "contour2d.pdf")
"""
