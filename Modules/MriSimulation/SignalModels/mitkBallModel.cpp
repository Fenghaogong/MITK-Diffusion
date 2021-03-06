/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center.

All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/
#include <vnl/vnl_cross.h>
#include <vnl/vnl_quaternion.h>
#include <mitkBallModel.h>

using namespace mitk;

template< class ScalarType >
BallModel< ScalarType >::BallModel()
    : m_Diffusivity(0.001)
{

}

template< class ScalarType >
BallModel< ScalarType >::~BallModel()
{

}

template< class ScalarType >
ScalarType BallModel< ScalarType >::SimulateMeasurement(unsigned int dir, GradientType& )
{
    ScalarType signal = 0;

    if (dir>=this->m_GradientList.size())
        return signal;

    GradientType g = this->m_GradientList[dir];
    ScalarType bVal = g.GetNorm(); bVal *= bVal;

    if (bVal>0.0001)
        signal = std::exp( -this->m_BValue * bVal * m_Diffusivity );
    else
        signal = 1;

    return signal;
}

template< class ScalarType >
typename BallModel< ScalarType >::PixelType BallModel< ScalarType >::SimulateMeasurement(GradientType& )
{
    PixelType signal;
    signal.SetSize(this->m_GradientList.size());

    for( unsigned int i=0; i<this->m_GradientList.size(); i++)
    {
        GradientType g = this->m_GradientList[i];
        ScalarType bVal = g.GetNorm(); bVal *= bVal;

        if (bVal>0.0001)
            signal[i] = std::exp( -this->m_BValue * bVal * m_Diffusivity );
        else
            signal[i] = 1;
    }

    return signal;
}
