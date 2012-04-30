#include "vectorization/PotraceTracer.h"
#include "imaging/WinBMP.h"
#include "imaging/VectorImage.h"
#include <fstream>
#include <iostream>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Vectorization;
using namespace std;

int main() {
  ifstream input("8bit.bmp");
  RasterImage* img = WinBMP::FromStream(input);

  ITracer* tracer = new PotraceTracer();

  VectorImage* vectImg = tracer->Trace(*img);

  cout << "Width: " << img->GetWidth() << "; Height: " << img->GetHeight() << endl;

  while (true) {
      int x;
      int y;

      cin >> x >> y;

      if (x == -1 && y == -1) {
          break;
      }

      ArgbQuad color = img->GetColor(x, y);

      cout << "Red: " << (int)color.red << " Green: " << (int)color.green << " Blue: " << (int)color.blue << endl;
  }

  delete img;
  delete tracer;
  delete vectImg;
}
