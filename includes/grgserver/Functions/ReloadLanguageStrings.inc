ReloadLanguageStrings()
{
	print("* Unloading language strings...");
	Count(id, LANGUAGE_MAXSTRINGS)
	{
		strdel(languageStrings[id][LANGUAGESTRING_ENGLISH], 0, STRINGLENGTH_LANGUAGESTRING);
		strdel(languageStrings[id][LANGUAGESTRING_GERMAN], 0, STRINGLENGTH_LANGUAGESTRING);
	}
	print("* Loading language strings...");
	mysql_query("SELECT * FROM `languagestrings`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new id = strval(GetMySQLField("ID"));
		if (id < LANGUAGE_MAXSTRINGS)
		{
			strcat(languageStrings[id][LANGUAGESTRING_ENGLISH], GetMySQLField("English"), STRINGLENGTH_LANGUAGESTRING);
			strcat(languageStrings[id][LANGUAGESTRING_GERMAN], GetMySQLField("German"), STRINGLENGTH_LANGUAGESTRING);
		}
		else
		{
			printf("Language string ID %d is greater than language array size (%d)", id, LANGUAGE_MAXSTRINGS);
			break;
		}
	}
}