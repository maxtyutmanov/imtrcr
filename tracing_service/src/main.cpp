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

  delete img;
  delete tracer;
  delete vectImg;
}
