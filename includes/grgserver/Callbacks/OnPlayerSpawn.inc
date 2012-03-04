public OnPlayerSpawn(playerid)
{
	if (IsPlayerNPC(playerid))
	{
		new npcName[MAX_PLAYER_NAME];
		GetPlayerName(playerid, npcName, sizeof(npcName));
		strdel(npcName, 0, 4);
		MySQLQuery("SELECT * FROM `npcs` WHERE `Name` = '%s'", MySQLEscapeString(npcName));
		mysql_store_result();
		if (floatstr(GetMySQLField("SpawnPosX")) || floatstr(GetMySQLField("SpawnPosY")) || floatstr(GetMySQLField("SpawnPosZ")))
		{
			FormatNew:command[100]("teleport %s %s %s %s 0", GetMySQLField("SpawnPosX"), GetMySQLField("SpawnPosY"), GetMySQLField("SpawnPosZ"), GetMySQLField("SpawnAngle"));
			SendNPCCommand(playerid, command);
		}
		mysql_free_result();
		return true;
	}
	if (GetPVar:playerid[SPAWNAFTERLOGIN])
	{
		SetPVar:playerid[SPAWNAFTERLOGIN](false);
		SetPlayerPos(playerid, floatstr(GetUserDBValue(playerid, "PosX")), floatstr(GetUserDBValue(playerid, "PosY")), floatstr(GetUserDBValue(playerid, "PosZ")));
		SetPlayerFacingAngle(playerid, floatstr(GetUserDBValue(playerid, "Angle")));
		SetPlayerInterior(playerid, strval(GetUserDBValue(playerid, "Interior")));
		SetPlayerSkin(playerid, GetPVar:playerid[SKIN]);
	}
	return true;
}