
#include <stdio.h>
#include <QApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <tesseract/baseapi.h>
#include <tesseract/renderer.h>
#include <tesseract/strngs.h>
#include <iostream>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  const QString tesseractDir(QLatin1String("C:/Program Files/Tesseract-OCR"));

  const QString imagePath = QCoreApplication::applicationDirPath()
    .append(QLatin1String("/image/5.png"));
  const std::string sImagePath = imagePath.toStdString();

  // Load image
  cv::Mat im = cv::imread(sImagePath);
  if (im.empty()) {
      std::cout << "Cannot open source image!" << std::endl;
      return -1;
  }
 
  cv::Mat gray;
  cv::cvtColor(im, gray, CV_BGR2GRAY);

  // ...other image pre-processing here...
  
  // Pass it to Tesseract API
  tesseract::TessBaseAPI tess;
  tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
  tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
  tess.SetImage((uchar*)gray.data, gray.cols, gray.rows, 1, gray.cols);
 
  // Get the text
  char* out = tess.GetUTF8Text();
  std::cout << out << std::endl;

  //return app.exec();
  return 0;
}
