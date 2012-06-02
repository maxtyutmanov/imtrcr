class ExternalSystemsController < ApplicationController

  def index
    @systems = ExternalSystem.all
  end
  
  def show
    id = params[:id]
    @system = ExternalSystem.find(id)
  end
  
  def new
    # default: render 'new' template
  end

  def create
    @system = ExternalSystem.create!(params[:system])
    flash[:notice] = "#{@system.name} was successfully created."
    redirect_to external_systems_path
  end

  def edit
    @system = ExternalSystem.find params[:id]
  end

  def update
    @system = ExternalSystem.find params[:id]
    @system.update_attributes!(params[:system])
    flash[:notice] = "#{@system.name} was successfully updated."
    redirect_to external_system_path(@system)
  end

  def destroy
    @system = ExternalSystem.find(params[:id])
    @system.destroy
    flash[:notice] = "External system '#{@system.name}' was deleted."
    redirect_to external_systems_path
  end

end
