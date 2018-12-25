int fastDoubleToInt(double doubleValue) {
	doubleValue += 6755399441055744.0; // 2^51 + 2^52
	return *(int *) &doubleValue;
}
