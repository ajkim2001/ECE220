// partners: aahant2, seltzer6
/*
Alex Kim netid:alexk4 5/2/2021
*/

#include "ComplexNumber.h"
#include "helper.h"

ComplexNumber::ComplexNumber()
{
    magnitude = 0;
    phase = 0;
    real_component = 0;
    imaginary_component = 0;
    number_type = COMPLEX;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
    magnitude = sqrt((real_component * real_component) + (imaginary_component * imaginary_component));
    phase = calculate_phase(real_component, imaginary_component);
    number_type = COMPLEX;
    }

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    magnitude = other.get_magnitude();
    phase = other.get_phase();
    real_component = other.get_real_component();
    imaginary_component = other.get_imaginary_component();
    number_type = other.get_number_type();
    }

void ComplexNumber::set_real_component (double rval)
{
    real_component = rval;
    magnitude = sqrt((rval * rval) + (imaginary_component * imaginary_component));
    phase = calculate_phase(rval, imaginary_component);
}

double ComplexNumber::get_real_component() const
{
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    imaginary_component = rval;
    magnitude = sqrt((rval * rval) + (real_component * real_component));
    phase = calculate_phase(real_component, rval);
    }

double ComplexNumber::get_imaginary_component() const
{
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    return magnitude;
}

double ComplexNumber::get_phase() const{
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component + arg.get_real_component(), imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component - arg.get_real_component(), imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */

    return ComplexNumber(((real_component * arg.get_real_component()) - (imaginary_component * arg.get_imaginary_component())), ((real_component * arg.get_imaginary_component()) + (arg.get_real_component() * imaginary_component)));
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber(((a * c) + (b * d)) / ((c * c) + (d * d)), ((b * c) - (a * d)) / ((c * c) + (d * d)));
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component + arg.get_real_component(), imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component - arg.get_real_component(), imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component * arg.get_real_component(), imaginary_component * arg.get_real_component());
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component / arg.get_real_component(), imaginary_component / arg.get_real_component());
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
    return ComplexNumber(real_component, imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component, imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber(-1 * imaginary_component * arg.get_imaginary_component(), real_component * arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber(imaginary_component / arg.get_imaginary_component(), -1 * real_component / arg.get_imaginary_component());
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}