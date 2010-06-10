% compile.m - Generated by CMakeLists.txt 
clear mex

files = {'tinysg.cpp', 'mex_command.cpp', };
libname = 'tinysg';
mexflags = '-g';
mexflags = [mexflags ' -DTIXML_USE_STL=1 -I/usr/local/include -I/usr/local/include -I/Users/yamokosk/Workspaces/tinysg -I/usr/local/include/boost-1_34_1'];
mexflags = [mexflags ' -L/usr/local/lib -L/Users/yamokosk/Workspaces/tinysg/build/tinysg'];
mexflags = [mexflags ' -llog4cxx -ltinysg'];
for file = files
	mexflags = [mexflags ' ' char(file)];
end

mexstr = ['mex ' mexflags];
fprintf('%s\n', mexstr);
eval(mexstr);

clear mexflags libname files;
%!cp tinysg.mexw32 ../tinysg.mexw32