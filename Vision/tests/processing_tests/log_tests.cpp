//
// Created by cameronearle on 12/25/16.
//

#include "gtest/gtest.h"
#include "../../processing/src/dataLogging/Log.hpp"

vector<string> splitElements(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;

    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

TEST(log_tests, log_debug_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStdout();
    Log::d("ld", "data");
    string raw = testing::internal::GetCapturedStdout();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[DEBUG]");
    ASSERT_EQ(split[2], "[ld]");
    ASSERT_EQ(split[3], "data\n");
    Log::close();
}

TEST(log_tests, log_debug_file_test) {
    Log::init(Log::Level::DEBUG, true, "res/testing.log");
    Log::d("ld", "data");
    Log::close();
    ifstream infile("res/testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3;
    infile.close();
    remove("res/testing.log");
    ASSERT_EQ(fromfile1, "[DEBUG]");
    ASSERT_EQ(fromfile2, "[ld]");
    ASSERT_EQ(fromfile3, "data");
}

TEST(log_tests, log_info_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStdout();
    Log::i("ld", "data");
    string raw = testing::internal::GetCapturedStdout();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[INFO]");
    ASSERT_EQ(split[2], "[ld]");
    ASSERT_EQ(split[3], "data\n");
    Log::close();
}

TEST(log_tests, log_info_file_test) {
    Log::init(Log::Level::DEBUG, true, "res/testing.log");
    Log::i("ld", "data");
    Log::close();
    ifstream infile("res/testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3;
    infile.close();
    remove("res/testing.log");
    ASSERT_EQ(fromfile1, "[INFO]");
    ASSERT_EQ(fromfile2, "[ld]");
    ASSERT_EQ(fromfile3, "data");
}

TEST(log_tests, log_warning_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStderr();
    Log::w("ld", "data");
    string raw = testing::internal::GetCapturedStderr();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[WARNING]");
    ASSERT_EQ(split[2], "[ld]");
    ASSERT_EQ(split[3], "data\n");
    Log::close();
}

TEST(log_tests, log_warning_file_test) {
    Log::init(Log::Level::DEBUG, true, "res/testing.log");
    Log::w("ld", "data");
    Log::close();
    ifstream infile("res/testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3;
    infile.close();
    remove("res/testing.log");
    ASSERT_EQ(fromfile1, "[WARNING]");
    ASSERT_EQ(fromfile2, "[ld]");
    ASSERT_EQ(fromfile3, "data");
}

TEST(log_tests, log_error_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStderr();
    Log::e("ld", "data");
    string raw = testing::internal::GetCapturedStderr();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[ERROR]");
    ASSERT_EQ(split[2], "[ld]");
    ASSERT_EQ(split[3], "data\n");
    Log::close();
}

TEST(log_tests, log_error_file_test) {
    Log::init(Log::Level::DEBUG, true, "res/testing.log");
    Log::e("ld", "data");
    Log::close();
    ifstream infile("res/testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3;
    infile.close();
    remove("res/testing.log");
    ASSERT_EQ(fromfile1, "[ERROR]");
    ASSERT_EQ(fromfile2, "[ld]");
    ASSERT_EQ(fromfile3, "data");
}

TEST(log_tests, log_exception_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStderr();
    Log::x("ld", "data");
    string raw = testing::internal::GetCapturedStderr();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[EXCEPTION]");
    ASSERT_EQ(split[2], "[ld]");
    ASSERT_EQ(split[3], "data\n");
    Log::close();
}

TEST(log_tests, log_exception_file_test) {
    Log::init(Log::Level::DEBUG, true, "res/testing.log");
    Log::x("ld", "data");
    Log::close();
    ifstream infile("res/testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3;
    infile.close();
    remove("res/testing.log");
    ASSERT_EQ(fromfile1, "[EXCEPTION]");
    ASSERT_EQ(fromfile2, "[ld]");
    ASSERT_EQ(fromfile3, "data");
}

TEST(log_tests, log_wtfomgy_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStderr();
    Log::wtfomgy("ld", "data");
    string raw = testing::internal::GetCapturedStderr();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[WHAT");
    ASSERT_EQ(split[2], "THE");
    ASSERT_EQ(split[3], "FRICK,");
    ASSERT_EQ(split[4], "OH");
    ASSERT_EQ(split[5], "MY");
    ASSERT_EQ(split[6], "GOD");
    ASSERT_EQ(split[7], "WHY?]");
    ASSERT_EQ(split[8], "[ld]");
    ASSERT_EQ(split[9], "data\n");
    Log::close();
}

TEST(log_tests, log_wtfomgy_file_test) {
    Log::init(Log::Level::DEBUG, true, "res/testing.log");
    Log::wtfomgy("ld", "data");
    Log::close();
    ifstream infile("res/testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    string fromfile4;
    string fromfile5;
    string fromfile6;
    string fromfile7;
    string fromfile8;
    string fromfile9;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3 >> fromfile4 >> fromfile5 >> fromfile6 >> fromfile7 >> fromfile8 >> fromfile9;
    infile.close();
    remove("res/testing.log");
    ASSERT_EQ(fromfile1, "[WHAT");
    ASSERT_EQ(fromfile2, "THE");
    ASSERT_EQ(fromfile3, "FRICK,");
    ASSERT_EQ(fromfile4, "OH");
    ASSERT_EQ(fromfile5, "MY");
    ASSERT_EQ(fromfile6, "GOD");
    ASSERT_EQ(fromfile7, "WHY?]");
    ASSERT_EQ(fromfile8, "[ld]");
    ASSERT_EQ(fromfile9, "data");
}