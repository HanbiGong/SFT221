#include "pch.h"
#include "CppUnitTest.h"
#include "customers_r.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <streambuf>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(CustomersTest)
    {
    public:

         // Black box test: Test the validity check of postal codes
        TEST_METHOD(ValidPostalCodeTest)
        {
            char formattedCode[POSTAL_CODE_SIZE];
            bool valid = isValidPostalCode("M5B2K1", formattedCode);
            Assert::IsTrue(valid);
            Assert::AreEqual("M5B 2K1", formattedCode);
        }

        // Black box test: Test with an invalid postal code
        TEST_METHOD(InvalidPostalCodeTest)
        {
            char formattedCode[POSTAL_CODE_SIZE];
            bool valid = isValidPostalCode("123 456", formattedCode);
            Assert::IsFalse(valid);
        }

        // White box test: Test specific rules of postal code formatting (e.g., space placement)
        TEST_METHOD(PostalCodeFormatTest)
        {
            char formattedCode[POSTAL_CODE_SIZE];
            isValidPostalCode("M5B2K1", formattedCode);
            Assert::AreEqual(' ', formattedCode[3]);
        }

        // White box test: Test boundary conditions (such as postal code length)
        TEST_METHOD(PostalCodeBoundaryTest)
        {
            char formattedCode[POSTAL_CODE_SIZE];
            bool valid = isValidPostalCode("M5B2K12", formattedCode);
            Assert::IsFalse(valid);
        }
    };
    TEST_CLASS(CustomerInfoValidationTest) 
    {
    public:
        // Black box test: Validate function with all fields correctly filled
        TEST_METHOD(ValidCustomerInfoTest)
        {
            struct Customer customer = { "John", "Park", "123 Main St", "Anytown", "Anystate", "M5B 2K1" };
            Assert::IsTrue(validateCustomerInfo(&customer));
        }

        // Black box test: Validate function with one empty field
        TEST_METHOD(EmptyFieldTest)
        {
            struct Customer customer = { "", "Park", "123 Main St", "Anytown", "Anystate", "M5B 2K1" };
            Assert::IsFalse(validateCustomerInfo(&customer));
        }

        // White box test: Test boundary condition with an almost empty field
        TEST_METHOD(BoundaryConditionTest)
        {
            struct Customer customer = { "J", "", "123 Main St", "Anytown", "Anystate", "M5B 2K1" };
            Assert::IsFalse(validateCustomerInfo(&customer));
        }

        // White box test: Test internal logic, such as checking order of fields
        TEST_METHOD(InternalLogicTest)
        {
            struct Customer customer = { "John", "", "", "Anytown", "Anystate", "M5B 2K7" };
            Assert::IsFalse(validateCustomerInfo(&customer));
        }
    };
}
