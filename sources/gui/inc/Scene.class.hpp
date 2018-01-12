// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Scene.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 10:05:10 by hestela           #+#    #+#             //
//   Updated: 2016/01/23 10:05:18 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SCENE_H
# define SCENE_H

# include <QGraphicsScene>
# include <QGraphicsSceneDragDropEvent>
# include <QMimeData>
# include <QUrl>

class Scene : public QGraphicsScene
{
	Q_OBJECT

	public:
		explicit Scene ( QObject *parent = 0 );
		~Scene ( void );

	protected:
		void	dragMoveEvent( QGraphicsSceneDragDropEvent* event );
		void	dropEvent( QGraphicsSceneDragDropEvent* event );

	signals:
		void	onDropFile ( std::string path );
};

#endif // SCENE_H
