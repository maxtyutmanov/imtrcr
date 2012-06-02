class EventsController < ApplicationController

  def index
    
    @events = Event.find(:all)
  
  end

end
