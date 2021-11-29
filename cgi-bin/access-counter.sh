#! /bin/sh

if [ -f ./counter.dat ] ; then
        read COUNT < counter.dat
else
        COUNT=1
fi

echo `expr $COUNT + 1` > counter.dat

echo 'HTTP/1.0 200 OK'
echo 'Content-Type: text/html'
echo ''
echo '<html>'
echo '<body>'
echo '<h2 align="center">A Simple Picture Library</h2>'
echo '<p align="center">'
echo '<img src="../day3/j1.jpg" width="180" height="180" hspace="5" />'
echo '<img src="../day3/j2.jpg" width="180" height="180" hspace="5" />'
echo '<img src="../day3/j3.jpg" width="180" height="180" hspace="5" />'
echo '<img src="../day3/j4.jpg" width="180" height="180" hspace="5" /></p>'
echo '<hr>'
echo -n '<p align="center">My clock says it is '
date "+%Y-%m-%d  %H:%M:%S"
echo '</p>'
echo -n '<p align="center">Access counter now : '
printf "%05d </p>\n" `expr $COUNT + 1`

echo '</body>'
echo '</html>'

