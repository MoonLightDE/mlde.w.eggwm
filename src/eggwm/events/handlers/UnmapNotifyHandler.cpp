/**
 * Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * @file /src/eggwm/events/handlers/UnmapNotifyHandler.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  UnmapNotifyHandler
 * @author José Expósito
 */
#include "UnmapNotifyHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

UnmapNotifyHandler::UnmapNotifyHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool UnmapNotifyHandler::processEvent(XEvent* event) {
    Window windowID = event->xunmap.window;
    qDebug() << "[+] UnmapNotify event 0x" << hex << windowID;

    // Si la ventana es un cliente
    if(this->wl->existClient(windowID)) {
        qDebug() << "\tLa ventana es un cliente";
        XWindow* xwindow = wl->getXWindowByClientID(windowID);

        // Si el cliente se desmapea porque se minimiza
        if(xwindow->getState() == IconicState) {
            qDebug() << "\tEl cliente se minimiza";

        // Si el cliente se desmapea porque pasa de NormalState a WithdrawnState
        } else {
            qDebug() << "\tEl cliente pasa de NormalState a WithdrawnState";
            xwindow->setState(WithdrawnState);

            qDebug() << "\tEliminando la ventana de la lista del EWMH";
            this->wl->removeFromManagedWindow(xwindow);
        }

        // Ponemos como ventana activa la de la parte superior de la pila
        qDebug() << "\tActualizando la ventana activa";
        this->wl->setActiveWindow(this->wl->getTopWindow());

        return false;

    // Si la ventana no es un cliente
    } else {
        qDebug() << "\tLa ventana no es un cliente";
        return false;
    }
}

#if QT_VERSION >= 0x050000
bool UnmapNotifyHandler::processEvent(xcb_generic_event_t* event) 
{
    xcb_unmap_notify_event_t* unmap = reinterpret_cast<xcb_unmap_notify_event_t*>(event);
    Window windowID = unmap->window;
    if (this->wl->existClient(windowID)) {
        XWindow* xwindow = wl->getXWindowByClientID(windowID);
        if (xwindow->getState() != IconicState) {
            xwindow->setState(WithdrawnState);
            this->wl->removeFromManagedWindow(xwindow);
        }
        this->wl->setActiveWindow(this->wl->getTopWindow());
    }
    return false;
}
#endif
