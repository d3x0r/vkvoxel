
@set SRCS=
@set SRCS= %SRCS%   cppmain.c 
@set SRCS= %SRCS%   define.c  
@set SRCS= %SRCS%   input.c   
@set SRCS= %SRCS%   fileio.c  
@set SRCS= %SRCS%   expr.c    

del panthers_c_preprocessor.c

ppc.exe -c -K -once -ssio -sd  -p -opanthers_c_preprocessor.c %SRCS%

:gcc -O3 -o ppc.exe panthers_c_preprocessor.c

:echo Please Update https://gist.github.com/d3x0r/8c8ab33cd7130c3c9983e12d354ad067

