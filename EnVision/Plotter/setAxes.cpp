#include "Plotter/initPlot.h"
#include "Base/envision.h"

//==============================================================================
// void Plot::xAxis(QString selection, int size_x)
//------------------------------------------------------------------------------
//==============================================================================
void Plot::xAxis(QString selection, int size_x)
{
		xVector.clear();
		xVector.reserve(size_x);

		//Image is non-spectral, make only ordinal scale available
		if (ImageAttribute::Record[_imgIndex].wavelength.size() == 1){

			if (selection.compare("ordinal") != 0) {
				ui_plot->radioButtonX01->setChecked(true);
				ui_plot->radioButtonX02->setEnabled(false);
			}

			for (size_t n = 1; n < (_channels+1); ++n) {
				xVector.push_back(n);
			}

			ui_plot->plot->xAxis->setRange(-5, _channels + 10);
			ui_plot->plot->xAxis->setLabel("Channel");
		} else {
			//Image is spectral, ordinal scale and a unit-specific scale are available
			int n = 0;
			ui_plot->radioButtonX02->setEnabled(true);
			for (std::vector<double>::iterator it = ImageAttribute::Record[_imgIndex].wavelength.begin(); it != ImageAttribute::Record[_imgIndex].wavelength.end(); ++it) {
				if (selection.compare("ordinal") == 0) {
					xVector.push_back(n);
					++n;
				}
				if (selection.compare("unit") == 0) {
					xVector.push_back(*it);
				}
			}

			if (selection.compare("ordinal") == 0) {
				ui_plot->plot->xAxis->setRange(-0.1, _channels + 0.1);
				ui_plot->plot->xAxis->setLabel("Channel");
			}

			if (selection.compare("unit") == 0) {
				ui_plot->plot->xAxis->setRange((double)(ImageAttribute::Record[_imgIndex].wavelength[0]) - 20,
					(double)(ImageAttribute::Record[_imgIndex].wavelength[_channels - 1]) + 20);
				ui_plot->plot->xAxis->setLabel(QString::fromStdString(ImageAttribute::Record[_imgIndex].wavelenunit));
			}

		}
		ui_plot->plot->replot();
	return;
}


//==============================================================================
// void Plot::yAxis(QString selection, int size_y)
//------------------------------------------------------------------------------
//==============================================================================
void Plot::yAxis(QString selection, int size_y)
{
		if (selection.compare("[0,1]") == 0) {
			ui_plot->plot->yAxis->setRange(-0.03, 1.05);
			ui_plot->plot->yAxis->setLabel("Reflectance mapped to [0,1]");
			this->normalize = 1;
			//main->Log(QString("Y-Axis is now labeled\n..'Spectral Reflectance'."));
		}
		else if (selection.compare(QString("[0," + QString::number((double)_maxDataVal) + "]")) == 0) {
			ui_plot->plot->yAxis->setRange(-5, (double)_maxDataVal + 500);
			ui_plot->plot->yAxis->setLabel("Reflectance mapped to max. sensor range");
			this->normalize = (double)_maxDataVal;
			//main->Log(QString("Y-Axis is now labeled\n.. 'Spectral Reflectance'."));
		}

		ui_plot->plot->replot();
	return;
}


