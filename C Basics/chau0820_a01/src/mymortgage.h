/**
 * mymortgage.h
 * header file contains function headers
 */
#ifndef MYMORTGAGE_H         // set compiling condition to avoid redefinition
#define MYMORTGAGE_H

/**
 * Compute the monthly payment of given mortgage princile, annual interest rate (%), and mortgage years. 
 *
 * @param principal_amount - float type.
 * @param annual_interest_rate - value of parcentage rate, e.g. 5 means 5%, float type.
 * @param years - number of mortgage year, int type.
 * @return - monthly payment, float type.
 */
float monthly_payment(float principal_amount, float annual_interest_rate, int years);


/**
 * Determine the total payment of loan given mortgage princile, annual interest rate (%), and mortgage years. 
 *
 * @param principal_amount - float type.
 * @param annual_interest_rate - value of parcentage rate, e.g. 5 means 5%, float type.
 * @param years - number of mortgage year, int type.
 * @return - the total payment of the loan, float type.
 */
float total_payment(float principal_amount, float annual_interest_rate, int years);


/**
 * Determine the total interested payed for the loan given mortgage princile, annual interest rate (%), and mortgage years. 
 *
 * @param principal_amount - float type.
 * @param annual_interest_rate - value of parcentage rate, e.g. 5 means 5%, float type.
 * @param years - number of mortgage year, int type.
 * @return - the total interest payed by the end of paying off the loan, float type.
 */
float total_interest(float principal_amount, float annual_interest_rate, int years);

#endif