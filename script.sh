rm -r Pictures
mkdir Pictures
rm -f video.h264
echo "taking pictures"
ssh -t pi@192.168.1.2 "raspivid -o video/video.h264 -rot 180 -t 6000"
echo "coping video from rapsi"
scp pi@192.168.1.2:~/video/video.h264 .
echo "extract pictures"
ffmpeg -i video.h264 -r 10 -f image2 Pictures/pic%03d.bmp
