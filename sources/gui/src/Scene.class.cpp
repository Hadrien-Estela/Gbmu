// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Scene.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 10:07:08 by hestela           #+#    #+#             //
//   Updated: 2016/01/23 10:07:18 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Scene.class.hpp"

Scene::Scene( QObject* parent ):
	QGraphicsScene(parent)
{ }

Scene::~Scene ( void )
{ }

void	Scene::dragMoveEvent( QGraphicsSceneDragDropEvent* event )
{
	event->acceptProposedAction();
}

void Scene::dropEvent( QGraphicsSceneDragDropEvent* event )
{
	if (event->mimeData()->hasUrls())
		emit onDropFile(event->mimeData()->urls().front().toLocalFile().toUtf8().constData());
}
