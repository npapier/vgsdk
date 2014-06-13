/**
 * @brief: simple examples of GoogleTest Macros
 */

// Function to test GoogleTest macro
bool pred1(int i)
{
	if (i > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool pred2(int i, int j)
{
	if (i > j)
	{
		return true;
	}
	else
	{
		return false;
	}
}

TEST_F(VgTestModel, DISABLED_MacroTest)
{
	bool t = true;
	bool f = false;
	
//Basic
	ASSERT_TRUE(t);
	EXPECT_TRUE(t);
	ASSERT_FALSE(f);
	EXPECT_FALSE(f);

//Binary comparaison
	int val1 = 1;
	int val2 = 1;

	//Equality
	ASSERT_EQ(val1, val2);
	EXPECT_EQ(val1, val2);
	
	//Difference
	val1 = 1;
	val2 = 2;
	ASSERT_NE(val1, val2);
	EXPECT_NE(val1, val2);

	//Lesser than
	ASSERT_LT(val1, val2);
	EXPECT_LT(val1, val2);

	ASSERT_LE(val1, val2);
	EXPECT_LE(val1, val2);

	//Greater than
	val1 = 2;
	val2 = 1;
	ASSERT_GT(val1, val2);
	EXPECT_GT(val1, val2);

	ASSERT_GE(val1, val2);
	EXPECT_GE(val1, val2);

//String comparison (for std::string use EXPECT/ASSERT_EQ)
	char str1[] = "aaa";
	char str2[] = "aaa";
	char str3[] = "bbb";
	char str4[] = "AAA";
	//Egalité
	ASSERT_STREQ(str1, str2);
	EXPECT_STREQ(str1, str2);
	
	//Différence
	ASSERT_STRNE(str1, str3);
	EXPECT_STRNE(str1, str3);

	//Egalité sans case sensitive
	ASSERT_STRCASEEQ(str1, str4);
	EXPECT_STRCASEEQ(str1, str4);

	//Différence sans case sensitive
	ASSERT_STRCASENE(str1, str3);
	EXPECT_STRCASENE(str1, str3);

//Explicite succes/failure
	SUCCEED();
	//FAIL();
	
//Exception test
	ASSERT_THROW({	std::string s = "s";
					throw s;
				}, std::string);
	EXPECT_THROW({	std::string s = "s";
					throw s;
				}, std::string);

	ASSERT_ANY_THROW({	std::string s = "s";
						throw s;
				});
	EXPECT_ANY_THROW({	std::string s = "s";
					throw s;
				});

	ASSERT_NO_THROW({int i = 0;});
	EXPECT_NO_THROW({int i = 0;});

//Predicate assertion
	ASSERT_PRED1(pred1, 1);
	EXPECT_PRED1(pred1, 1);

	ASSERT_PRED2(pred2, 2, 1);
	EXPECT_PRED2(pred2, 2, 1);

//Float comparison
	float f1 = 1.123;
	float f2 = 1.123;

	double d1 = 1.123;
	double d2 = 1.123;

	ASSERT_FLOAT_EQ(f1, f2);
	EXPECT_FLOAT_EQ(f1, f2);

	ASSERT_DOUBLE_EQ(d1, d2);
	EXPECT_DOUBLE_EQ(d1, d2);

	ASSERT_NEAR(1.123, 1.124, 0.01);
	EXPECT_NEAR(1.123, 1.124, 0.01);

//Type assertion
	::testing::StaticAssertTypeEq<int, int>();

//Death test
	ASSERT_DEATH({assert(false);}, "");
	EXPECT_DEATH({assert(false);}, ""); 

	ASSERT_EXIT({exit(0);}, ::testing::ExitedWithCode(0), "");
	EXPECT_EXIT({exit(0);}, ::testing::ExitedWithCode(0), "");
}