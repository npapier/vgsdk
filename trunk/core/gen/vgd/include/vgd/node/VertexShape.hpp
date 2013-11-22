	/**
	 * @brief Invalidate bounding box dirty flag for each parents of this node.
	 */
	void invalidateParentsBoundingBoxDirtyFlag();

	/**
	 * @name Bounding box
	 */
	//@{

	/**
	 * @brief Compute the bounding box.
	 *
	 * @remarks It computes the bounding box using only the vertex field (the vertexIndex field is not used, if there is 
	 * unused vertex, then the bounding box could be less accurate).
	 *
	 * @remarks Compute only if bounding box dirty flag is invalidate (i.e. Mesh has changed).
	 *
	 * @return true if bounding box has been computed, false if bounding box has been already valid or simply transformed
	 * by the matrix \c transformation.
	 */
	bool computeBoundingBox( const vgm::MatrixR& transformation );

	bool isBoundingBoxValid() const;

	/**
	 * @brief Compute the bounding box.
	 * 
	 * The bounding box is compute using vertex and vertexIndex field. So a unused vertex don't modify the bounding box.
	 * This is slower than the simple computeBoundingBox() but always accurate.
	 * 
	 * @remarks Compute only if bounding box dirty flag is invalidate (but be carefull bounding box dirty flag is only 
	 * invalidate if a vertex has changed and NOT vertex index !!!).
	 * 
	 * @remarks Compute only if bounding box dirty flag is invalidate (i.e. Mesh has changed).
	 *
	 * @return true if bounding box has been computed, false if bounding box has been already valid or simply transformed
	 * by the matrix \c transformation.
	 */
	bool smartComputeBoundingBox( const vgm::MatrixR& transformation );
	
	void invalidateBoundingBox( bool bInvalidate = true );

	//@}



	/**
	 * @name Actions on VertexShape
	 */
	//@{

	void transform( const vgm::MatrixR& matrix, const bool normalize = true );

	void transform( const vgm::Vec3f translation );

	void transform( const vgm::Rotation rotation );

	void scale( const vgm::Vec3f scale );

	/**
	* @brief	Check the texture coordinates dimension and call the template texutureTransform method to
	*			transform the texture coordinates at the given index with the given matrix.
	* 
	* @param matrix the transformation matrix
	*
	* @param texUnit the texture unit index
	*/
	void textureTransform( const vgm::MatrixR& matrix, const int texUnit = 0 );

	/**
	* @brief Transform the texture coordinates at the given index with the given matrix.
	* 
	* @param matrix the transformation matrix
	*
	* @param texUnit the texture unit index
	*/
	template< typename T >
	void textureTransform( const vgm::MatrixR& matrix, const int texUnit )
	{
		vgd::field::EditorRW< T > texCoords	= getTexCoordRW< T >( texUnit );

		// Transform each texCoord
		for(	T::iterator	i	= texCoords->begin(),
							ie	= texCoords->end();
				i != ie;
				++i )
		{
			matrix.multVecMatrix( (*i), (*i) );
		}
	};

	//@}


	/**
	 * @name Accessors to field \c texCoord*
	 */
	//@{

	/**
	 * @brief Typedef for the \c texCoord field.
	 */
	typedef vgd::field::MFFloat	FTexCoord1fType;
	
	/**
	 * @brief Typedef for the \c texCoord field.
	 */
	typedef vgd::field::MFVec2f	FTexCoord2fType;

	/**
	 * @brief Typedef for the \c texCoord field.
	 */	
	typedef vgd::field::MFVec3f	FTexCoord3fType;

	/**
	 * @brief Typedef for the \c texCoord field.
	 */
	typedef vgd::field::MFVec4f	FTexCoord4fType;

	/**
	 * @brief Typedef for the \c texCoord value.
	 */
	typedef float				TexCoord1fValueType;
	
	/**
	 * @brief Typedef for the \c texCoord value.
	 */
	typedef vgm::Vec2f			TexCoord2fValueType;
	
	/**
	 * @brief Typedef for the \c texCoord value.
	 */
	typedef vgm::Vec3f			TexCoord3fValueType;
	
	/**
	 * @brief Typedef for the \c texCoord value.
	 */
	typedef vgm::Vec4f			TexCoord4fValueType;


	/**
	 * @brief Returns true if the specified field is existing.
	 *
	 * @param index		zero-base index for the \c texCoord field.
	 */
	const bool hasTexCoord( const uint index ) const;

	/**
	 * @brief Returns the dimension of the i-th \c texCoord field.
	 * 
	 * @param index		zero-base index for the \c texCoord field.
	 * 
	 * @return The dimension of the texture coordinates for the i-th \c texCoord field (zero is returned if there is no
	 * texture coordinate for the specified field).
	 * 
	 * @remarks Expected values are 0, 1, 2, 3 and 4.
	 */
	const int8 getTexCoordDim( const int32 index ) const;


	/**
	 * @brief Accessor to \c texCoord field.
	 * 
	 * @param index		zero-base index for the \c texCoord field.
	 */
	template< typename FTexCoordType >
	vgd::field::EditorRO< FTexCoordType > getTexCoordRO( const int32 index = 0 ) const
	{
		return ( getFieldRO< FTexCoordType >(getFTexCoord( index )) );
	}

	/**
	 * @brief Accessor to \c texCoord field.
	 * 
	 * @param index		zero-base index for the \c texCoord field.
	 */
	template< typename FTexCoordType >
	vgd::field::EditorRW< FTexCoordType > getTexCoordRW( const int32 index = 0 )
	{
		return ( getFieldRW< FTexCoordType >(getFTexCoord( index )) );
	}

	/**
	 * @brief Call this method to create dynamically one or more \c texCoord and \c texCoordBinding fields with the 
	 * specified dimensions (for the coordinate).
	 * 
	 * \c texCoord fields should have preferably contiguous index. If not, only the first block (starting from index 0) 
	 * of contiguous \c texCoord would be used.
	 * A field \c texCoord with an index of \c i is used with the texture (Texture2D, Texture3D...) that has a multi 
	 * attribute index of \c i.
	 * 
	 * @param texCoordDimension		dimension of the texture coordinate (1, 2, 3 or 4)
	 * @param index				zero-base index for the \c texCoord field
	 * @param num				number of contiguous fields
	 * 
	 * @remarks Call this method before any access to texture coordinate or binding related methods with a specific 
	 * index.
	 * 
	 * @remarks Texture coordinates and bindings, initialized by this method, must not be already created.
	 */
	void createTexUnits( const int8 texCoordDimension = 2, const int32 index = 0, const int32 num = 1 );

	/**
	 * @brief Call this method to remove dynamically one \c or more texCoord and \c texCoordBinding fields.
	 * 
	 * @param index					zero-base index for the \c texCoord field.
	 * @param num					number of contiguous fields.
	 * 
	 * @remarks Texture coordinates and bindings, initialized by this method, must be already created.
	 */
	void removeTexUnits( const int32 index = 0, const int32 num = 1 );

	/**
	 * @brief Returns the number of texture units actually used by this node.
	 *
	 * @return The number of texture units.
	 */
	const int32 getNumTexUnits() const;


	// Iterators
	typedef std::set< uint > IndexSet;
	typedef IndexSet::const_iterator ConstIteratorIndexSet;
	const std::pair< ConstIteratorIndexSet, ConstIteratorIndexSet > getTexUnitsIterators() const;

private:
	typedef std::pair< ConstIteratorIndexSet, ConstIteratorIndexSet > PairConstIteratorIndexSet;
	typedef IndexSet::iterator IteratorIndexSet;
	IndexSet m_texUnitsIndexSet;

	/**
	 * @brief Call this method to create dynamically one or more \c texCoord and \c texCoordBinding fields with the 
	 * specified \c fieldType and for all the desired textures units.
	 * 
	 * @param index					zero-base index for the \c texCoord field.
	 * @param num					number of contiguous fields.
	 */
	template< typename fieldType >
	void createTexUnits( const int32 index, const int32 num )
	{
		// Adds fields
		int32	i32Max = index + num;

		for(	int32 i32 = index;
				i32 < i32Max;
				++i32 )
		{
			addField( new fieldType(getFTexCoord(i32)) );
			addField( new FTexCoordBindingType(getFTexCoordBinding(i32)) );

			assert( m_texUnitsIndexSet.find( i32 ) == m_texUnitsIndexSet.end() );
			m_texUnitsIndexSet.insert( i32 );
		}
		
		// Links
		for(	int32 i32 = index;
				i32 < i32Max;
				++i32 )
		{
			link( getFTexCoord(i32), getDFNode() );
			link( getFTexCoordBinding(i32), getDFNode() );
		}

		// Defaults bindings
		for(	int32 i32 = index;
				i32 < i32Max;
				++i32 )
		{
			setTexCoordBinding( i32, vgd::node::BIND_OFF );
		}
	}
public:
	//@}


	/**
	 * @name Accessors to field \c texCoordBinding*
	 */
	//@{

	/**
	 * @brief Typedef for the \c texCoordBinding field.
	 */	
	typedef vgd::field::SFBinding		FTexCoordBindingType;

	/**
	 * @brief Typedef for the \c texCoordBinding value.
	 */
	typedef vgd::node::Binding	TexCoordBindingValueType;

	const vgd::node::Binding	getTexCoordBinding( const int32 texUnit ) const;
	void 						setTexCoordBinding( const int32 texUnit, const vgd::node::Binding );

	//@}


	/**
	 * @brief Returns the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit.
	 * 
	 * @return the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit.
	 */
	static const std::string getFTexCoord( const int32 textureUnit );

	/**
	 * @brief Returns the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit \c binding.
	 * 
	 * @return the name of field \c texture \c coordinates \c of \c the \c specified \c texture \c unit \c binding.
	 */
	static const std::string getFTexCoordBinding( const int32 textureUnit );
