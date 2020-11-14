#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{  
	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); 
}

bool CellPosition::SetVCell(int v) 
{
	if (v >= 0 && v <= (NumVerticalCells-1))
	{
		vCell = v;
		return true;
	}
	else 
	{
	return false;
	}
}

bool CellPosition::SetHCell(int h) 
{
	if (h >= 0 && h <= (NumHorizontalCells-1))
	{
		hCell = h;
		return true;
	}
	else 
	{
	return false;
	}
}
int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const 
{
	if (hCell >= 0 && hCell <= (NumHorizontalCells-1))
	{
		if (vCell >= 0 && vCell <= (NumVerticalCells-1))
			if (GetCellNum() >= 1 && GetCellNum() <= 99)
				return true;
	}
	return false;
	}
int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition (*this);
}
int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	if ( cellPosition.HCell() != -1 && cellPosition.VCell() != -1  )
	{
		int CellNum = ((NumVerticalCells-1) - cellPosition.VCell()) * NumHorizontalCells + (cellPosition.HCell() + 1);
		return CellNum;
	}
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	CellPosition x;
	if ( cellNum >= 1 && cellNum <= 99 )
	{
		if (cellNum % NumHorizontalCells != 0)
		{
			x.SetVCell(((NumVerticalCells-1) - (cellNum / NumHorizontalCells)));
			x.SetHCell(((cellNum % NumHorizontalCells) - 1));
		}
		else
		{
			x.SetVCell((NumVerticalCells - (cellNum / (NumHorizontalCells-1))));
			x.SetHCell((NumHorizontalCells-1));
		}
	}
	else 
	{
		x.SetHCell(-1);
		x.SetVCell(-1);
	}
		return x;
	} 

void CellPosition::AddCellNum (int addedNum)
{
	
		int x = GetCellNum() + addedNum;
		if (x >= 0 && x <= 99)
		{
			CellPosition y(x);
			SetHCell(y.HCell());
			SetVCell(y.VCell());
		}
		if ( x > 99)
		{
		   SetHCell(NumHorizontalCells -1);
		   SetVCell(0);
 		}
		if ( x < 0)
		{
		   SetHCell(0);
		   SetVCell(NumVerticalCells-1);
		}
}
