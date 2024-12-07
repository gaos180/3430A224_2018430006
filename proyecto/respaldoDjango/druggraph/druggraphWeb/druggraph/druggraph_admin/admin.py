from django.contrib import admin
from .models import Target, Drug, InteractionDt

class ConsultaTarget(admin.ModelAdmin):
    list_display = ('target_id', 'name')
    search_fields = ('target_id', 'name')

class ConsultaDrug(admin.ModelAdmin):
    list_display = ('drug_id', 'name')
    search_fields = ('drug_id', 'name')

class ConsultaDrugTarget(admin.ModelAdmin):
    list_display = ('drug_name', 'target_name', 'type_interaction')  # Usamos funciones para mostrar los nombres
    search_fields = ('drug_drug__name', 'target_target__name', 'type_interaction')  # Búsqueda basada en llaves foráneas

    # Función para mostrar el nombre del fármaco (Drug) relacionado
    def drug_name(self, obj):
        return obj.drug_drug.name if obj.drug_drug else None
    drug_name.short_description = 'Drug Name'

    # Función para mostrar el nombre del objetivo (Target) relacionado
    def target_name(self, obj):
        return obj.target_target.name if obj.target_target else None
    target_name.short_description = 'Target Name'

admin.site.register(Target, ConsultaTarget)
admin.site.register(Drug, ConsultaDrug)
admin.site.register(InteractionDt, ConsultaDrugTarget)

