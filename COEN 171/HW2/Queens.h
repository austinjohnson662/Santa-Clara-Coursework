# ifndef QUEENS_H
# define QUEENS_H
# include <cstdlib>


// An abstract chess piece that cannot be instantiated.

class Piece {
protected:
    int _row, _column;

public:
    int row() const {
		return _row;
    }

    int column() const {
		return _column;
    }

    void place(int row, int column) {
		_row = row;
		_column = column;
    }

    virtual bool menaces(const Piece *p) const = 0;
};


class Rook : virtual public Piece {
	public:
		virtual bool menaces(const Piece *p) const {
			return (_row == p->row())||(_column == p->column());
		}
};

class Knight : virtual public Piece {
	public:
		virtual bool menaces(const Piece *p) const {
			int rows = abs(_row - p->row());
			int columns = abs(_column - p->column());
			return (rows == 2 && columns == 1)||(rows == 1 && columns == 2);
		}
};

class Bishop : virtual public Piece {
	public:
		virtual bool menaces(const Piece *p) const{
			int rows = abs(_row - p->row());
			int columns = abs(_column - p->column());
			return rows == columns;
		}
};

class Queen : virtual public Rook, virtual public Bishop {
	public:	
		virtual bool menaces(const Piece *p) const {
			return Rook::menaces(p)|| Bishop::menaces(p);
		}
};

class Amazon : virtual public Queen, virtual public Knight{
	public:
		virtual bool menaces(const Piece *p) const {
			return Queen::menaces(p)||Knight::menaces(p);
		}
};

# endif /* QUEENS_H */
