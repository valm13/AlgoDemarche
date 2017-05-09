mkdir Pictures
mkdir video
rm -f Pictures/*.jpeg
rm -f video/video.h264
raspivid -o video/video.h264 -t $1
ffmpeg -i video/video.h264 -r 10 -f image2 Pictures/pic%03d.bmp
