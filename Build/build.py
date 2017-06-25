import os, sys, shutil, argparse
from functools import partial
from scripts import cmake
import subprocess
import traceback

def checkPythonVer(in_ver):
	py_ver = sys.version_info[:2]
	if py_ver >= in_ver:
		raise Exception("Incompatible python version: need %s", str(py_ver))
		
def clearDir(dir):
	if os.path.exists(dir):
		shutil.rmtree(dir)
	pass
		
def main():
	#checkPythonVer((2,7))
	
	parser = argparse.ArgumentParser()
	parser.add_argument('--goal', type=str, help='goal of the build. Build third-party dependencies, build client-tools or both. (tools_build)')
	parser.add_argument('--out', type=str, help='output folder')
	
	args = parser.parse_args()
	
	cur_file_dir = os.path.dirname(os.path.realpath(__file__))
	source_dir = os.path.dirname(cur_file_dir)
	root_dir = root_dir = os.path.dirname(source_dir)
	cmake_dir = os.path.join(source_dir, "utils/cmake-3.2.1/bin")

	out_folder = 'out32'
	if args.out == None:
		raise Exception("Not set output folder")
	
	out_folder = os.path.join(root_dir, args.out) 
	out_bin = os.path.join(out_folder, 'bin')
	
	cmake.Config.cmake_exe = os.path.join(cmake_dir, 'cmake.exe')
	
	specs = dict()
	
	specs['avis_dep'] = {
		'gen_id': 'vc140',
		'amd64': False,
		'xpSupport': True,
		'source_dir': source_dir,
		'out_dir': out_folder,
		'bin_dir': out_bin,
		#'args': {
		#},
		'install': True
	}
	
	specs['avis'] = {
		'gen_id': 'vc140',
		'amd64': False,
		'xpSupport': True,
		'source_dir': source_dir,
		'out_dir': out_folder,
		'bin_dir': out_bin,
		#'args': {
		#},
		'install': True
	}
	
	proj_deps = cmake.Config('avis_dep', **specs['avis_dep'])
	proj = cmake.Config('avis', **specs['avis'])
	
	try:
		if args.goal == None:
			raise Exception("Not goal argument")
		elif args.goal == 'tools_build':
			print("begin")
			proj_deps.generate()
			proj_deps.build('Debug')
			proj_deps.build('Release')
			proj.generate()
			proj.build('Debug')
			proj.build('Release')
		
	except Exception:
		print(sys.exc_info()[0])
		print(sys.exc_info()[1])
		
	return 1
	
if __name__ == "__main__": 
	main()	
	
